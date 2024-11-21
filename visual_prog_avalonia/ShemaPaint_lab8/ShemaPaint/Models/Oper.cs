using DynamicData.Binding;
using YamlDotNet.Serialization;

namespace ShemaPaint.Models
{
    public class Oper : AbstractNotifyPropertyChanged
    {
        private string opName = string.Empty, opType = string.Empty, opVid = string.Empty, opSter = string.Empty;
        private string parName = string.Empty, parType = string.Empty;

        [YamlMember(typeof(string))]
        public string OpName
        {
            get => opName;
            set => SetAndRaise(ref opName, value);
        }
        [YamlMember(typeof(string))]
        public string OpType
        {
            get => opType;
            set => SetAndRaise(ref opType, value);
        }
        [YamlMember(typeof(string))]
        public string OpVidim
        {
            get => opVid;
            set => SetAndRaise(ref opVid, value);
        }
        [YamlMember(typeof(string))]
        public string OpSter
        {
            get => opSter;
            set => SetAndRaise(ref opSter, value);
        }
        [YamlMember(typeof(string))]
        public string ParName
        {
            get => parName;
            set => SetAndRaise(ref parName, value);
        }
        [YamlMember(typeof(string))]
        public string ParType
        {
            get => parType;
            set => SetAndRaise(ref parType, value);
        }
    }
}
