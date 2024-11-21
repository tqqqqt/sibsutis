using ReactiveUI;
using ShemaPaint.Models;

namespace ShemaPaint.ViewModels
{
    public class ChangeFormWindowViewModel : ViewModelBase
    {
        // perem
        private El_Class? classElement;
        private El_Interface? interfaceElement;
        private double width, height, fontSizeFirst;

        // canstr
        public ChangeFormWindowViewModel()
        {
            classElement = null;
            interfaceElement = null;
        }
        public ChangeFormWindowViewModel(El_Class formClassElement)
        {
            classElement = formClassElement;
            interfaceElement = null;
            Width = classElement.Width;
            Height = classElement.Height;
            FontSizeFirst = classElement.FontSizeMain;
        }
        public ChangeFormWindowViewModel(El_Interface formInterfaceElement)
        {
            classElement = null;
            interfaceElement = formInterfaceElement;
            Width = interfaceElement.Width;
            Height = interfaceElement.Height;
            FontSizeFirst = interfaceElement.FontSizeMain;
        }


        // option
        public double Width
        {
            get => width;
            set => this.RaiseAndSetIfChanged(ref width, value);
        }
        public double Height
        {
            get => height;
            set => this.RaiseAndSetIfChanged(ref height, value);
        }
        public double FontSizeFirst
        {
            get => fontSizeFirst;
            set => this.RaiseAndSetIfChanged(ref fontSizeFirst, value);
        }


        // function
        public void ButtonSave()
        {
            if (classElement != null)
            {
                classElement.Width = Width;
                classElement.Height = Height;
                classElement.FontSizeMain = FontSizeFirst;
            }
            else if (interfaceElement != null)
            {
                interfaceElement.Width = Width;
                interfaceElement.Height = Height;
                interfaceElement.FontSizeMain = FontSizeFirst;
            }
        }
    }
}
