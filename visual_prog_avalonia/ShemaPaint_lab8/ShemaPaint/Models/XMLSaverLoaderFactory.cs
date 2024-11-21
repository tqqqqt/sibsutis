using System.IO;

namespace ShemaPaint.Models
{
    public class XMLSaverLoaderFactory : ISaverLoaderFactory
    {
        public IColectionLoader CreateLoader()
        {
            return new XMLLoader();
        }

        public IColectionSaver CreateSaver()
        {
            return new XMLSaver();
        }

        public bool IsMatch(string path)
        {
            return ".xml".Equals(Path.GetExtension(path));
        }
    }
}
