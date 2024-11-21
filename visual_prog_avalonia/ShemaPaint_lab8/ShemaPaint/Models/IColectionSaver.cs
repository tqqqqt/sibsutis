using System.Collections.Generic;

namespace ShemaPaint.Models
{
    public interface IColectionSaver
    {
        void Save(IEnumerable<IFigures> colection, string path);
    }
}
