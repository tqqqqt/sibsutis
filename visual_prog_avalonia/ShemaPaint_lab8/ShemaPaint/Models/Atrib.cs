using DynamicData.Binding;
using YamlDotNet.Serialization;

namespace ShemaPaint.Models
{
    public class Atrib : AbstractNotifyPropertyChanged
    {
        private string vidim, stereot, name, type, atribValue;

        public Atrib()
        {
            vidim = string.Empty;
            stereot = string.Empty;
            name = string.Empty;
            type = string.Empty;
            atribValue = string.Empty;
        }

        [YamlMember(typeof(string))]
        public string Name
        {
            get => name;
            set => SetAndRaise(ref name, value);
        }
        [YamlMember(typeof(string))]
        public string Type
        {
            get => type;
            set => SetAndRaise(ref type, value);
        }
        [YamlMember(typeof(string))]
        public string Vidim
        {
            get => vidim;
            set => SetAndRaise(ref vidim, value);
        }
        [YamlMember(typeof(string))]
        public string AtribValue
        {
            get => atribValue;
            set => SetAndRaise(ref atribValue, value);
        }
        [YamlMember(typeof(string))]
        public string Stereot
        {
            get => stereot;
            set => SetAndRaise(ref stereot, value);
        }
    }
}
