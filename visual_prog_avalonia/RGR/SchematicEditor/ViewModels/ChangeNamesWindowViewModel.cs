using ReactiveUI;
using SchematicEditor.Models;
using System.Collections.ObjectModel;

namespace SchematicEditor.ViewModels
{
    public class ChangeNamesWindowViewModel : ViewModelBase
    {
        private Project? curentProject;
        private ObservableCollection<Schema>? schemaColection;
        private string? projectName;

        public ChangeNamesWindowViewModel()
        {
            curentProject = null;
            projectName = string.Empty;
            schemaColection = null;
        }

        public ChangeNamesWindowViewModel(Project tempProject)
        {
            CurentProject = tempProject;
        }

        public Project CurentProject
        {
            get => curentProject;
            set
            {
                this.RaiseAndSetIfChanged(ref curentProject, value);
                ProjectName = CurentProject.Name;
                SchemaColection = CurentProject.SchemaColection;
            }
        }

        public string ProjectName
        {
            get => projectName;
            set
            {
                this.RaiseAndSetIfChanged(ref projectName, value);
                CurentProject.Name = projectName;
            }
        }

        public ObservableCollection<Schema> SchemaColection
        {
            get => schemaColection;
            set => this.RaiseAndSetIfChanged(ref schemaColection, value);
        }
    }
}
