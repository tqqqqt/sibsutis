using System.IO;

namespace ShemaPaint.Models
{
    public class YAMLSaverLoaderFactory : ISaverLoaderFactory
    {
        public IColectionLoader CreateLoader()
        {
            return new YAMLLoader();
        }

        public IColectionSaver CreateSaver()
        {
            return new YAMLSaver();
        }

        public bool IsMatch(string path)
        {
            return ".yaml".Equals(Path.GetExtension(path));
        }
    }
}
