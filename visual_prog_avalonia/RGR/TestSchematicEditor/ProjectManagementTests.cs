using Avalonia.Controls;
using Avalonia.VisualTree;
using SchematicEditor.ViewModels;
using SchematicEditor.Views;

namespace TestSchematicEditor
{
    public class ProjectManagementTests
    {
        [Fact]
        public async void CreateNewProjectTest()
        {
            var app = AvaloniaApp.GetApp();
            var mainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(100);

            var buttonCreate = mainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonCreate");
            await Task.Delay(50);
            mainWindow.ClickCreateButton(buttonCreate, null);

            var schemaWindow = (SchemaWindow)app.Windows.First(b => b.Title == "RGR - Schema Window");
            var schemaWindowDataContext = schemaWindow.DataContext as SchemaWindowViewModel;

            await Task.Delay(50);
            schemaWindow.CreateProject(null, null);
            await Task.Delay(50);

            int needCoutSchem = 1;
            string needNameProject = "Проект", needNameSchema1 = "схема 1";

            int curentCountSchema = schemaWindowDataContext.CurentSchemaList.Count();
            Assert.Equal(needCoutSchem, curentCountSchema);

            string curentNameSchema1 = schemaWindowDataContext.CurentSchemaList[0].Name;
            Assert.Equal(needNameSchema1, curentNameSchema1);

            string curentNameProject = schemaWindowDataContext.CurentNameProject;
            Assert.Equal(needNameProject, curentNameProject);
        }

        [Fact]
        public async void AddedSchemaTest()
        {
            var app = AvaloniaApp.GetApp();
            var mainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(100);

            var buttonCreate = mainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonCreate");
            await Task.Delay(50);
            mainWindow.ClickCreateButton(buttonCreate, null);

            var schemaWindow = (SchemaWindow)app.Windows.First(b => b.Title == "RGR - Schema Window");
            var schemaWindowDataContext = schemaWindow.DataContext as SchemaWindowViewModel;

            schemaWindow.AddedSchemINProject(null, null);
            schemaWindow.AddedSchemINProject(null, null);

            int needCountSchem = 3;
            string needNameSchema2 = "схема 2", needNameSchema3 = "схема 3";

            int curentCountSchema = schemaWindowDataContext.CurentSchemaList.Count();
            Assert.Equal(needCountSchem, curentCountSchema);

            var curentNameSchema2 = schemaWindowDataContext.CurentSchemaList[1].Name;
            Assert.Equal(needNameSchema2, curentNameSchema2);

            var curentNameSchema3 = schemaWindowDataContext.CurentSchemaList[2].Name;
            Assert.Equal(needNameSchema3, curentNameSchema3);
        }

    }
}
