using System.Collections.Generic;
using System.IO;
using System.Text.Json;

namespace Graphic.Models
{
    public class JsonFunction
    {
        public JsonFunction() { }

        public void JsonSave(IList<IFigure> figures_colection, string path)
        {
            using (FileStream fs = new FileStream(path, FileMode.OpenOrCreate))
            {
                JsonSerializer.Serialize(fs, figures_colection,
                    new JsonSerializerOptions
                    {
                        Converters = { new ShapeJsonConverter() },
                        WriteIndented = true
                    }); ;
            }
        }

        public IEnumerable<IFigure> JsonLoad(string path)
        {
            using (FileStream fs = new FileStream(path, FileMode.OpenOrCreate))
            {
                List<IFigure>? load_colection = JsonSerializer.Deserialize<List<IFigure>>(fs,
                    new JsonSerializerOptions
                    {
                        Converters = { new ShapeJsonConverter() },
                        WriteIndented = true
                    });

                if (load_colection == null)
                {
                    load_colection = new List<IFigure>();
                }

                return load_colection;
            }
        }
    }
}
