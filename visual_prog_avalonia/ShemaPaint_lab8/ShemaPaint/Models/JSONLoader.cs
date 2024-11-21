using System.Collections.Generic;
using System.IO;
using System.Text.Json;

namespace ShemaPaint.Models
{
    public class JSONLoader : IColectionLoader
    {
        public IEnumerable<IFigures> Load(string path)
        {
            using (FileStream fileStream = new FileStream(path, FileMode.OpenOrCreate))
            {
                List<IFigures>? loadColection = JsonSerializer.Deserialize<List<IFigures>>(fileStream,
                    new JsonSerializerOptions
                    {
                        Converters = { new ELementsJsonConverter() },
                        WriteIndented = true
                    });
                if (loadColection == null)
                {
                    loadColection = new List<IFigures>();
                }
                return loadColection;
            }
        }
    }
}
