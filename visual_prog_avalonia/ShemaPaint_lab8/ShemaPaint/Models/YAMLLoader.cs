using System.Collections.Generic;
using System.IO;
using YamlDotNet.Serialization;
using YamlDotNet.Serialization.NamingConventions;

namespace ShemaPaint.Models
{
    public class YAMLLoader : IColectionLoader
    {
        public IEnumerable<IFigures> Load(string path)
        {
            string fileString = File.ReadAllText(path);
            var deserializer = new DeserializerBuilder()
                .WithNamingConvention(CamelCaseNamingConvention.Instance)
                .WithTagMapping("!class", typeof(El_Class))
                .WithTagMapping("!interface", typeof(El_Interface))
                .WithTagMapping("!lineNasled", typeof(LineNasled))
                .WithTagMapping("!lineRealiz", typeof(LineRealiz))
                .WithTagMapping("!lineZavis", typeof(LineZavis))
                .WithTagMapping("!lineAgreg", typeof(LineAgreg))
                .WithTagMapping("!lineCompos", typeof(LineCompos))
                .WithTagMapping("!lineAcos", typeof(LineAsoc))
                .Build();
            var stringDeserializ = deserializer.Deserialize<List<IFigures>>(fileString);
            if (stringDeserializ == null)
            {
                stringDeserializ = new List<IFigures>();
            }
            return stringDeserializ;
        }
    }
}
