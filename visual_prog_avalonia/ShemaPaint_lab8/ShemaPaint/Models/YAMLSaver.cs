using System.Collections.Generic;
using System.IO;
using YamlDotNet.Serialization;
using YamlDotNet.Serialization.NamingConventions;

namespace ShemaPaint.Models
{
    public class YAMLSaver : IColectionSaver
    {
        public void Save(IEnumerable<IFigures> colection, string path)
        {
            var serializer = new SerializerBuilder()
                 .WithNamingConvention(CamelCaseNamingConvention.Instance)
                 .WithTagMapping("!class", typeof(El_Class))
                 .WithTagMapping("!interface", typeof(El_Interface))
                 .WithTagMapping("!lineNasled", typeof(LineNasled))
                 .WithTagMapping("!lineRealiz", typeof(LineRealiz))
                 .WithTagMapping("!lineZavis", typeof(LineZavis))
                 .WithTagMapping("!lineAgreg", typeof(LineAgreg))
                 .WithTagMapping("!lineCompos", typeof(LineCompos))
                 .WithTagMapping("!lineAcos", typeof(LineAsoc))
                 .WithIndentedSequences()
                 .Build();
            var yaml = serializer.Serialize(colection);
            using (StreamWriter writer = new StreamWriter(path, false))
            {
                writer.WriteLine(yaml);
            }
        }
    }
}
