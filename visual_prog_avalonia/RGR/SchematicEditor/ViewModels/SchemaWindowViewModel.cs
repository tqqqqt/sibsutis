using ReactiveUI;
using SchematicEditor.Models;
using SchematicEditor.Views;
using System;
using System.Collections.ObjectModel;

namespace SchematicEditor.ViewModels
{
    public class SchemaWindowViewModel : ViewModelBase
    {
        private Project? curentProject;
        private Schema? curentSchemaEdit;
        private ObservableCollection<ISchemaObject> curentSchemaElement;
        private ObservableCollection<Schema> curentSchemaList;
        private string curentNameSchema, curentNameProject;

        public SchemaWindowViewModel()
        {
            CreateNewProject();
        }

        public SchemaWindowViewModel(string tempPath)
        {
            LoadProjectXML(tempPath);
        }


        public Project CurentProject
        {
            get => curentProject;
            set
            {
                this.RaiseAndSetIfChanged(ref curentProject, value);
                CurentNameProject = curentProject.Name;
                CurentSchemaList = curentProject.SchemaColection;
            }
        }

        public string CurentNameProject
        {
            get => curentNameProject;
            set => this.RaiseAndSetIfChanged(ref curentNameProject, value);
        }

        public ObservableCollection<Schema> CurentSchemaList
        {
            get => curentSchemaList;
            set => this.RaiseAndSetIfChanged(ref curentSchemaList, value);
        }

        public Schema CurentSchemaEdit
        {
            get => curentSchemaEdit;
            set
            {
                this.RaiseAndSetIfChanged(ref curentSchemaEdit, value);
                CurentColectionElement = curentSchemaEdit.ElementColection;
                CurentNameSchema = curentSchemaEdit.Name;
            }
        }

        public string CurentNameSchema
        {
            get => curentNameSchema;
            set => this.RaiseAndSetIfChanged(ref curentNameSchema, value);

        }

        public ObservableCollection<ISchemaObject> CurentColectionElement
        {
            get => curentSchemaElement;
            set => this.RaiseAndSetIfChanged(ref curentSchemaElement, value);
        }


        public void UpdateNames()
        {
            CurentNameSchema = CurentSchemaEdit.Name;
            CurentNameProject = CurentProject.Name;
        }

        public void CreateNewProject()
        {
            curentProject = new Project
            {
                Name = "Проект",
            };
            CurentProject = curentProject;
            CurentSchemaEdit = curentProject.SchemaColection[0];
            CurentColectionElement = CurentSchemaEdit.ElementColection;
        }

        public void CreateNewSchema()
        {
            CurentSchemaList.Add(new Schema
            {
                Name = "схема " + (CurentProject.SchemaColection.Count + 1).ToString(),
            });
        }

        public void SaveProjectXML(string path)
        {
            UpdateIndexElements();
            XMLSaver xmlSaver = new XMLSaver();
            xmlSaver.SaverProject(CurentProject, path);
        }

        public void LoadProjectXML(string path)
        {
            XMLLoader xmlLoader = new XMLLoader();
            CurentProject = xmlLoader.LoadProject(path);
            CurentSchemaEdit = CurentSchemaList[0];
            SchemaLine tempLine = new SchemaLine();
            tempLine.LoadConectionUpdate(CurentSchemaList);
        }

        public void SaveProgramHistory(MainWindowViewModel mainViewModel, string tempPath)
        {
            XMLSaver xmlSaver = new XMLSaver();
            mainViewModel.ColectionProjectHistory.Add(new ProjectHistory
            {
                Name = System.IO.Path.GetFileNameWithoutExtension(tempPath),
                Path = tempPath,
            });
            xmlSaver.SaverHistory(mainViewModel.ColectionProjectHistory, new ProjectHistory
            {
                Name = System.IO.Path.GetFileNameWithoutExtension(tempPath),
                Path = tempPath,
            });
        }

        public void DeleteSchemaElement(ISchemaElement tempElement)
        {
            try
            {
                for (int i = CurentColectionElement.Count - 1; i >= 0; i--)
                {
                    if (CurentColectionElement[i] is SchemaLine tempLine)
                    {
                        if (tempLine.FirstElement == tempElement) CurentColectionElement.RemoveAt(i);
                        else if (tempLine.SecondElement == tempElement) CurentColectionElement.RemoveAt(i);
                    }
                    else if (CurentColectionElement[i] is ISchemaElement tempColectionElement)
                    {
                        if (tempColectionElement == tempElement)
                        {
                            CurentColectionElement.RemoveAt(i);
                            break;
                        }
                    }
                }
            }
            catch (Exception error)
            {
                var errorWindow = new ErrorWindow(error.Message);
                errorWindow.Show();
            }
        }

        public void DeleteSchemaLine(SchemaLine tempLine)
        {
            CurentColectionElement.Remove(tempLine);
        }

        public void DeleteSchema(Schema tempSchema)
        {
            if (CurentSchemaList.Count > 1)
            {
                CurentSchemaList.Remove(tempSchema);
                CurentSchemaEdit = CurentSchemaList[0];
            }
            else
            {
                var errorWindow = new ErrorWindow("Должна быть одна схема в проекте.");
                errorWindow.Show();
            }
        }

        public void UpdateIndexElements()
        {
            foreach (Schema tempSchema in CurentProject.SchemaColection)
            {
                foreach (ISchemaObject tempObject in tempSchema.ElementColection)
                {
                    if (tempObject is ISchemaElement tempSchemaElement)
                    {
                        tempSchemaElement.IndexElement = tempSchema.ElementColection.IndexOf(tempSchemaElement);
                    }
                }
                foreach (ISchemaObject tempObject in tempSchema.ElementColection)
                {
                    if (tempObject is SchemaLine tempSchemaLine)
                    {
                        tempSchemaLine.IndexFirstElement = tempSchemaLine.FirstElement.IndexElement;
                        tempSchemaLine.IndexSecondElement = tempSchemaLine.SecondElement.IndexElement;
                    }
                }
            }
        }
    }
}
