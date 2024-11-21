﻿﻿using System.IO;

namespace SchematicEditor.Models
{
    public class XMLSaverLoader
    {
        protected readonly string historyPath = "../../../historyProject.xml";

        public bool CheckExistFile()
        {
            return File.Exists(historyPath);
        }
    }
}
