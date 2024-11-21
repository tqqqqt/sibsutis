using System.Collections.Generic;
using System.IO;
using System.Text.Json;

namespace ShemaPaint.Models
{
    public class JSONSaver : IColectionSaver
    {
        public void Save(IEnumerable<IFigures> colection, string path)
        {
            using (FileStream fs = new FileStream(path, FileMode.OpenOrCreate))
            {
                JsonSerializer.Serialize(fs, colection, new JsonSerializerOptions
                {
                    Converters = { new ELementsJsonConverter() },
                    WriteIndented = true
                });
            }
        }
    }
}
