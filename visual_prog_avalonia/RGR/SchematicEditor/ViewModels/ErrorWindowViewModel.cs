using ReactiveUI;

namespace SchematicEditor.ViewModels
{
    public class ErrorWindowViewModel : ViewModelBase
    {
        private string errorMesage;

        public ErrorWindowViewModel(string sendMesage)
        {
            errorMesage = string.Empty;
            ErrorMesage = sendMesage;
        }

        public string ErrorMesage
        {
            get => errorMesage;
            set => this.RaiseAndSetIfChanged(ref errorMesage, value);
        }
    }
}
