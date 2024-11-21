using ReactiveUI;
using SchematicEditor.Models;
using System.Collections.ObjectModel;

namespace SchematicEditor.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        private ObservableCollection<ProjectHistory>? colectionProjectHistory;

        public MainWindowViewModel()
        {
            var xmlLoader = new XMLLoader();
            if (xmlLoader.CheckExistFile() == true)
            {
                ColectionProjectHistory = new ObservableCollection<ProjectHistory>(xmlLoader.LoadHistory());
            }
            else
            {
                colectionProjectHistory = new ObservableCollection<ProjectHistory>();
            }
        }


        public ObservableCollection<ProjectHistory> ColectionProjectHistory
        {
            get => colectionProjectHistory;
            set => this.RaiseAndSetIfChanged(ref colectionProjectHistory, value);
        }


        public void DeleteProjectInHistory(ProjectHistory tempProject)
        {
            ColectionProjectHistory.Remove(tempProject);
            XMLSaver xmlSaver = new XMLSaver();
            xmlSaver.SaverHistroyNoNew(ColectionProjectHistory);
        }
    }
}