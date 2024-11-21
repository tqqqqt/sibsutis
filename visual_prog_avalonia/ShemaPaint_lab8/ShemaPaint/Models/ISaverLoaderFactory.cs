namespace ShemaPaint.Models
{
    public interface ISaverLoaderFactory
    {
        IColectionLoader CreateLoader();
        IColectionSaver CreateSaver();

        bool IsMatch(string path);
    }
}
