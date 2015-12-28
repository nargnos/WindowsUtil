using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.IO.MemoryMappedFiles;
using Microsoft.Win32.SafeHandles;
using Wapper.PeDecoderWapper;
namespace PeExplorer
{
    public class PeFile
    {
        private SafeMemoryMappedViewHandle smmv;
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
                if (pe == null)
                {
                    pe = new PeImage();
                }
                return pe;
            }
        }
        public bool IsOpen
        {
            get
            {
                return PE.IsAttached;
            }
        }
        public void Close()
        {
            if (PE.IsAttached)
            {
                PE.Dettach();
                OnEventNotify(Closed);
            }
            if (smmv != null)
            {
                smmv.ReleasePointer();
                smmv = null;
            }
        }
        public bool Open(string path, bool isReadOnly)
        {

            Close();
            IntPtr ptr;
            FileAccess fileAccess = isReadOnly ? FileAccess.Read : FileAccess.ReadWrite;
            MemoryMappedFileAccess memoryMappedFileAccess = isReadOnly ? MemoryMappedFileAccess.Read : MemoryMappedFileAccess.ReadWrite;
            var tmpFileName = Path.GetFileName(path);

            using (FileStream fs = new FileStream(path, FileMode.Open, fileAccess, FileShare.Read))
            using (MemoryMappedFile mmf = MemoryMappedFile.CreateFromFile(
                fs,
                tmpFileName,
                0,
                memoryMappedFileAccess, HandleInheritability.None, true)
                )
            using (var va = mmf.CreateViewAccessor(0, 0, memoryMappedFileAccess))
            {
                smmv = va.SafeMemoryMappedViewHandle;
                unsafe
                {
                    byte* pointer = null;
                    smmv.AcquirePointer(ref pointer);
                    ptr = new IntPtr(pointer);
                }
            }


            var result = PE.Attach(ptr, false);
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
