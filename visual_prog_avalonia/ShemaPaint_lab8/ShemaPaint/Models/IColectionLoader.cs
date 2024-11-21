using System.Collections.Generic;

namespace ShemaPaint.Models
{
    public interface IColectionLoader
    {
        IEnumerable<IFigures> Load(string path);
    }
}
