using ReactiveUI;
using ShemaPaint.Models;
using System.Collections.ObjectModel;

namespace ShemaPaint.ViewModels
{
    public class ChangeOptionWindowViewModel : ViewModelBase
    {
        // perem
        private El_Class? classElement;
        private El_Interface? interfaceElement;
        // first 
        private string name = string.Empty, stereotip = string.Empty, vidimost = string.Empty;
        private int stereotInd = 0, vidimInd = 0;

        // second
        private int vidInd2 = 0, sterInd2 = 0, selectIndex2 = 0;
        private string atName = string.Empty, atType = string.Empty, atValue = string.Empty, atVid = string.Empty, atSter = string.Empty;

        // third
        private int vidInd3 = 0, sterInd3 = 0, selectIndex3 = 0;
        private string opName = string.Empty, opType = string.Empty, parName = string.Empty, parType = string.Empty, opVid = string.Empty, opSter = string.Empty;


        // constr
        public ChangeOptionWindowViewModel()
        {
            classElement = null;
            interfaceElement = null;
        }
        public ChangeOptionWindowViewModel(El_Class changeElement)
        {
            classElement = changeElement;
            interfaceElement = null;
        }

        public ChangeOptionWindowViewModel(El_Interface changeElement)
        {
            classElement = null;
            interfaceElement = changeElement;
        }

        // option
        // first
        public string Name
        {
            get => name;
            set => this.RaiseAndSetIfChanged(ref name, value);
        }
        private string Stereotip
        {
            get => stereotip;
            set => this.RaiseAndSetIfChanged(ref stereotip, value);
        }
        private string Vidimost
        {
            get => vidimost;
            set => this.RaiseAndSetIfChanged(ref vidimost, value);
        }
        public int StereotInd
        {
            get => stereotInd;
            set
            {
                this.RaiseAndSetIfChanged(ref stereotInd, value);
                if (StereotInd == 1) Stereotip = "static";
                else if (StereotInd == 2) Stereotip = "abstract";
                else Stereotip = string.Empty;
            }
        }
        public int VidimInd
        {
            get => vidimInd;
            set
            {
                this.RaiseAndSetIfChanged(ref vidimInd, value);
                if (VidimInd == 1) Vidimost = "public";
                else if (VidimInd == 2) Vidimost = "Private";
                else Vidimost = string.Empty;
            }
        }

        // second
        public ObservableCollection<Atrib> AtribColection
        {
            get => CheckColectionAtrib();
        }
        public string AtName
        {
            get => atName;
            set => this.RaiseAndSetIfChanged(ref atName, value);
        }
        public string AtType
        {
            get => atType;
            set => this.RaiseAndSetIfChanged(ref atType, value);
        }
        public string AtValue
        {
            get => atValue;
            set => this.RaiseAndSetIfChanged(ref atValue, value);
        }
        private string AtVid
        {
            get => atVid;
            set => this.RaiseAndSetIfChanged(ref atVid, value);
        }
        private string AtSter
        {
            get => atSter;
            set => this.RaiseAndSetIfChanged(ref atSter, value);
        }
        public int VidInd2
        {
            get => vidInd2;
            set
            {
                this.RaiseAndSetIfChanged(ref vidInd2, value);
                if (VidInd2 == 1) AtVid = "+";
                else if (VidInd2 == 2) AtVid = "-";
                else if (VidInd2 == 3) AtVid = "#";
                else if (VidInd2 == 4) AtVid = "readonly";
                else if (VidInd2 == 5) AtVid = "static";
                else AtVid = string.Empty;
            }
        }
        public int SterInd2
        {
            get => sterInd2;
            set
            {
                this.RaiseAndSetIfChanged(ref sterInd2, value);
                if (SterInd2 == 1) AtSter = "event";
                else if (SterInd2 == 2) AtSter = "property";
                else if (SterInd2 == 3) AtSter = "required";
                else AtSter = string.Empty;
            }
        }
        public int SelectIndex2
        {
            get => selectIndex2;
            set => this.RaiseAndSetIfChanged(ref selectIndex2, value);
        }

        // third
        public ObservableCollection<Oper> OperColection
        {
            get => CheckColectionOper();
        }
        public string OpName
        {
            get => opName;
            set => this.RaiseAndSetIfChanged(ref opName, value);
        }
        public string OpType
        {
            get => opType;
            set => this.RaiseAndSetIfChanged(ref opType, value);
        }
        public string ParName
        {
            get => parName;
            set => this.RaiseAndSetIfChanged(ref parName, value);
        }
        public string ParType
        {
            get => parType;
            set => this.RaiseAndSetIfChanged(ref parType, value);
        }
        private string OpVid
        {
            get => opVid;
            set => this.RaiseAndSetIfChanged(ref opVid, value);
        }
        private string OpSter
        {
            get => opSter;
            set => this.RaiseAndSetIfChanged(ref opSter, value);
        }
        public int VidInd3
        {
            get => vidInd3;
            set
            {
                this.RaiseAndSetIfChanged(ref vidInd3, value);
                if (VidInd3 == 1) OpVid = "+";
                else if (VidInd3 == 2) OpVid = "-";
                else if (VidInd3 == 3) OpVid = "#";
                else if (VidInd3 == 4) OpVid = "readonly";
                else if (VidInd3 == 5) OpVid = "static";
                else OpVid = string.Empty;
            }
        }
        public int SterInd3
        {
            get => sterInd3;
            set
            {
                this.RaiseAndSetIfChanged(ref sterInd3, value);
                if (SterInd3 == 1) OpSter = "event";
                else if (SterInd3 == 2) OpSter = "property";
                else if (SterInd3 == 3) OpSter = "required";
                else OpSter = string.Empty;
            }
        }
        public int SelectIndex3
        {
            get => selectIndex3;
            set => this.RaiseAndSetIfChanged(ref selectIndex3, value);
        }


        // function
        // first
        public void ButtonAdd1()
        {
            if (classElement != null)
            {
                if (string.IsNullOrWhiteSpace(Name) == false &&
                    string.IsNullOrWhiteSpace(Stereotip) == false && string.IsNullOrWhiteSpace(Vidimost) == false)
                {
                    classElement.Name = Name;
                    classElement.Stereotip = Stereotip;
                    classElement.Vidimost = Vidimost;
                }
            }
            else if (interfaceElement != null)
            {
                if (string.IsNullOrWhiteSpace(Name) == false &&
                    string.IsNullOrWhiteSpace(Stereotip) == false && string.IsNullOrWhiteSpace(Vidimost) == false)
                {
                    interfaceElement.Name = Name;
                    interfaceElement.Stereotip = Stereotip;
                    interfaceElement.Vidimost = Vidimost;
                }
            }
        }
        public void ButtonClear1()
        {
            Name = string.Empty;
            Stereotip = string.Empty;
            StereotInd = 0;
            Vidimost = string.Empty;
            VidimInd = 0;
        }

        // second
        private ObservableCollection<Atrib> CheckColectionAtrib()
        {
            if (classElement != null) return classElement.Atrib_colection;
            else if (interfaceElement != null) return interfaceElement.AtribColection;
            return null;
        }
        public void ButtonAdd2()
        {
            if (classElement != null)
            {
                if (string.IsNullOrWhiteSpace(AtName) == false && string.IsNullOrWhiteSpace(AtType) == false &&
                    (string.IsNullOrWhiteSpace(AtVid) == false || VidInd2 != 0) &&
                    string.IsNullOrWhiteSpace(AtValue) == false &&
                    (string.IsNullOrWhiteSpace(AtSter) == false || SterInd2 != 0))
                {
                    classElement.Atrib_colection.Add(new Atrib
                    {
                        Name = AtName,
                        Type = AtType,
                        Vidim = AtVid,
                        AtribValue = AtValue,
                        Stereot = AtSter,
                    });
                }
            }
            else if (interfaceElement != null)
            {
                if (string.IsNullOrWhiteSpace(AtName) == false && string.IsNullOrWhiteSpace(AtType) == false &&
                    (string.IsNullOrWhiteSpace(AtVid) == false || VidInd2 != 0) &&
                    string.IsNullOrWhiteSpace(AtValue) == false &&
                    (string.IsNullOrWhiteSpace(AtSter) == false || SterInd2 != 0))
                {
                    interfaceElement.AtribColection.Add(new Atrib
                    {
                        Name = AtName,
                        Type = AtType,
                        Vidim = AtVid,
                        AtribValue = AtValue,
                        Stereot = AtSter,
                    });
                }
            }
        }
        public void ButtonClear2()
        {
            AtName = string.Empty;
            AtType = string.Empty;
            AtValue = string.Empty;
            VidInd2 = 0;
            SterInd2 = 0;
            SelectIndex2 = -2;
        }
        public void ButtonDelete2()
        {
            if (classElement != null)
            {
                if (SelectIndex2 >= 0)
                {
                    classElement.Atrib_colection.RemoveAt(SelectIndex2);
                }
            }
            else if (interfaceElement != null)
            {
                if (SelectIndex2 >= 0)
                {
                    interfaceElement.AtribColection.RemoveAt(SelectIndex2);
                }
            }
            SelectIndex2 = -2;
        }

        // third
        private ObservableCollection<Oper> CheckColectionOper()
        {
            if (classElement != null) return classElement.Oper_colection;
            else if (interfaceElement != null) return interfaceElement.OperColection;
            return null;
        }
        public void ButtonAdd3()
        {
            if (classElement != null)
            {
                if (string.IsNullOrWhiteSpace(OpName) == false && string.IsNullOrWhiteSpace(OpType) == false &&
                    (string.IsNullOrWhiteSpace(OpVid) == false || VidInd3 != 0) &&
                    (string.IsNullOrWhiteSpace(OpSter) == false || SterInd3 != 0) &&
                    string.IsNullOrWhiteSpace(ParName) == false && string.IsNullOrWhiteSpace(ParType) == false)
                {
                    classElement.Oper_colection.Add(new Oper
                    {
                        OpName = OpName,
                        OpType = OpType,
                        OpVidim = OpVid,
                        OpSter = OpSter,
                        ParName = ParName,
                        ParType = ParType,
                    });
                }
            }
            else if (interfaceElement != null)
            {
                if (string.IsNullOrWhiteSpace(OpName) == false && string.IsNullOrWhiteSpace(OpType) == false &&
                    (string.IsNullOrWhiteSpace(OpVid) == false || VidInd3 != 0) &&
                    (string.IsNullOrWhiteSpace(OpSter) == false || SterInd3 != 0) &&
                    string.IsNullOrWhiteSpace(ParName) == false && string.IsNullOrWhiteSpace(ParType) == false)
                {
                    interfaceElement.OperColection.Add(new Oper
                    {
                        OpName = OpName,
                        OpType = OpType,
                        OpVidim = OpVid,
                        OpSter = OpSter,
                        ParName = ParName,
                        ParType = ParType,
                    });
                }
            }
        }
        public void ButtonClear3()
        {
            OpName = string.Empty;
            OpType = string.Empty;
            ParName = string.Empty;
            ParType = string.Empty;
            VidInd3 = 0;
            SterInd3 = 0;
            SelectIndex3 = -2;
        }
        public void ButtonDelete3()
        {
            if (classElement != null)
            {
                if (SelectIndex3 >= 0)
                {
                    classElement.Oper_colection.RemoveAt(SelectIndex3);
                }
            }
            else if (interfaceElement != null)
            {
                if (SelectIndex3 >= 0)
                {
                    interfaceElement.OperColection.RemoveAt(SelectIndex3);
                }
            }
            SelectIndex3 = -2;
        }
    }
}
