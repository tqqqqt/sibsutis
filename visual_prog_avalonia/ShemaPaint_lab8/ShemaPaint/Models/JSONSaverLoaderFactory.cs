using System.IO;

namespace ShemaPaint.Models
{
    public class JSONSaverLoaderFactory : ISaverLoaderFactory
    {
        public IColectionLoader CreateLoader()
        {
            return new JSONLoader();
        }

        public IColectionSaver CreateSaver()
        {
            return new JSONSaver();
        }

        public bool IsMatch(string path)
        {
            return ".json".Equals(Path.GetExtension(path));
        }
    }
}
