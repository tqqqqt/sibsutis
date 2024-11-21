using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FileNotepad.Models
{
    public abstract class FilesAndDir
    {
        public FilesAndDir(string name)
        {
            Name = name;
        }
        public string Name { get; set; }
        public string Path { get; set; }
        public string Image { get; set; }
    }
}
