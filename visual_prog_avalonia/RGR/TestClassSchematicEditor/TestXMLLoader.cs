using SchematicEditor.Models;
using System.Collections.ObjectModel;

namespace TestClassSchematicEditor
{
    public class TestXMLLoader
    {
        [Fact]
        public void TestXMLLoadHistory()
        {
            XMLLoader xmlLoader = new XMLLoader();
            ObservableCollection<ProjectHistory> testColection = new ObservableCollection<ProjectHistory>(xmlLoader.LoadHistory());

            int countColection = 3;
            string nameFirstElement = "temp1";
            string pathFirstElement = "temp1/temp1/temp1";
            string nameSecondElement = "temp2";
            string pathSecondElement = "temp2/temp2/temp2";
            string nameThirdElement = "temp3";
            string pathThirdElement = "path3/path3/path3";

            int curentCountElements = testColection.Count;
            Assert.Equal(countColection, curentCountElements);

            string tempCheckName = testColection[0].Name;
            Assert.Equal(nameFirstElement, tempCheckName);
            string tempCheckPath = testColection[0].Path;
            Assert.Equal(pathFirstElement, tempCheckPath);

            tempCheckName = testColection[1].Name;
            Assert.Equal(nameSecondElement, tempCheckName);
            tempCheckPath = testColection[1].Path;
            Assert.Equal(pathSecondElement, tempCheckPath);

            tempCheckName = testColection[2].Name;
            Assert.Equal(nameThirdElement, tempCheckName);
            tempCheckPath = testColection[2].Path;
            Assert.Equal(pathThirdElement, tempCheckPath);
        }

        [Fact]
        public void TestXMLLoadProject()
        {
            XMLLoader xmlLoader = new XMLLoader();
            Project testProject = xmlLoader.LoadProject("../../../saveProjectForTest.xml");

            string nameProject = "Проект тест";
            int schemaCount = 1;
            string nameSchema = "схема тест";
            int countSchemaElements = 7;

            string curentNameProject = testProject.Name;
            Assert.Equal(nameProject, curentNameProject);

            int curentSchemaCount = testProject.SchemaColection.Count;
            Assert.Equal(schemaCount, curentSchemaCount);

            string curentNameSchema = testProject.SchemaColection[0].Name;
            Assert.Equal(nameSchema, curentNameSchema);

            int curentCountSchemaElements = testProject.SchemaColection[0].ElementColection.Count;
            Assert.Equal(countSchemaElements, curentCountSchemaElements);
        }

        [Fact]
        public void TestExistFile()
        {
            XMLLoader xmlLoader = new XMLLoader();

            bool existElement = File.Exists("../../../historyProject.xml");

            bool curentExistElement = xmlLoader.CheckExistFile();
            Assert.Equal(existElement, curentExistElement);
        }
    }
}
