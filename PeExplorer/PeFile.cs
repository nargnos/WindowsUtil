using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.IO.MemoryMappedFiles;
using Microsoft.Win32.SafeHandles;
using PeImageClr;
using System.Drawing;

namespace PeExplorer
{
    public class PeFile
    {
        private SafeMemoryMappedViewHandle smmv;
        private FileStream fs;
        private MemoryMappedFile mmf;
        private MemoryMappedViewAccessor mmva;

        private PeImage pe;
        private string fileName;

        public event Action Closed;
        public event Action Opened;
        private void OnEventNotify(Action action)
        {
            if (action != null)
            {
                action();
            }
        }
        public string FileName
        {
            get
            {
                return fileName;
            }
        }
        public PeImage PE
        {
            get
            {
                //if (pe == null)
                //{
                //    pe = new PeImage();
                //}
                return pe;
            }
        }
        public bool IsOpen
        {
            get
            {
                return true;// PE.IsAttached;
            }
        }
        public void Close()
        {
            //if (PE.IsAttached)
            //{
            //    PE.Dettach();
            //    OnEventNotify(Closed);
            //}
            if (smmv != null)
            {
                smmv.ReleasePointer();
                smmv = null;
            }
            if (mmva != null)
            {
                // mmva.Dispose(); 会自己析构不用管，下同
                mmva = null;
            }
            if (mmf != null)
            {
                mmf = null;
            }
            if (fs!=null)
            {
                fs.Close();
                fs = null;
            }
        }
        public bool Open(string path, bool isReadOnly)
        {

            Close();
            FileAccess fileAccess = isReadOnly ? FileAccess.Read : FileAccess.ReadWrite;
            MemoryMappedFileAccess memoryMappedFileAccess = isReadOnly ? MemoryMappedFileAccess.Read : MemoryMappedFileAccess.ReadWrite;
            var tmpFileName = Path.GetFileName(path);

            fs = new FileStream(path, FileMode.Open, fileAccess, FileShare.Read);
            mmf = MemoryMappedFile.CreateFromFile(
                fs,
                tmpFileName,
                0,
                memoryMappedFileAccess, HandleInheritability.None, true);

            mmva = mmf.CreateViewAccessor(0, 0, memoryMappedFileAccess);

            smmv = mmva.SafeMemoryMappedViewHandle;
            bool result = false;
            unsafe
            {
                byte* pointer = null;
                smmv.AcquirePointer(ref pointer);
                if (pointer == null)
                {
                    throw new FileLoadException("无法载入文件");
                }
               pe=new PeImage(pointer, false);
                result = true;
            }
            
            if (result)
            {
                fileName = tmpFileName;
                OnEventNotify(Opened);
            }
            else
            {
                fileName = string.Empty;
                throw new InvalidDataException("不是PE文件");
            }
            return result;

        }
    }
}
