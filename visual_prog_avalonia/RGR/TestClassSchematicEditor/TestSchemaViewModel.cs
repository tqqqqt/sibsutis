using SchematicEditor.Models;
using SchematicEditor.ViewModels;
using System.Collections.ObjectModel;

namespace TestClassSchematicEditor
{
    public class TestSchemaViewModel
    {
        [Fact]
        public void TestConstructorCreateNewProject()
        {
            SchemaWindowViewModel schemaViewModel = new SchemaWindowViewModel();
            string nameProject = "Проект";
            string nameEditSchema = "схема 1";
            string nameFirstSchema = "схема 1";

            string curentNameProject = schemaViewModel.CurentNameProject;
            Assert.Equal(nameProject, curentNameProject);

            string curentNameEditSchema = schemaViewModel.CurentNameSchema;
            Assert.Equal(nameEditSchema, curentNameEditSchema);

            string curentNameFirstSchema = schemaViewModel.CurentSchemaList[0].Name;
            Assert.Equal(nameFirstSchema, curentNameFirstSchema);
        }

        [Fact]
        public void CreateNewSchema()
        {
            SchemaWindowViewModel schemaViewModel = new SchemaWindowViewModel();
            schemaViewModel.CreateNewSchema();
            schemaViewModel.CreateNewSchema();

            string nameSecondSchema = "схема 2";
            string nameThirdSchema = "схема 3";

            string curentNameSecondSchema = schemaViewModel.CurentSchemaList[1].Name;
            Assert.Equal(nameSecondSchema, curentNameSecondSchema);

            string curentNameThirdSchema = schemaViewModel.CurentSchemaList[2].Name;
            Assert.Equal(nameThirdSchema, curentNameThirdSchema);
        }

        [Fact]
        public void TestLoadConstructor()
        {
            SchemaWindowViewModel schemaViewModel = new SchemaWindowViewModel("../../../saveProjectForTest.xml");

            int countElements = 7;
            string nameProject = "Проект тест";
            string nameSchema = "схема тест";

            int curentCountElements = schemaViewModel.CurentColectionElement.Count;
            Assert.Equal(countElements, curentCountElements);

            string curentNameProject = schemaViewModel.CurentNameProject;
            Assert.Equal(nameProject, curentNameProject);

            string curentNameSchemaList = schemaViewModel.CurentSchemaList[0].Name;
            Assert.Equal(nameSchema, curentNameSchemaList);

            string curentNameSchemaEdit = schemaViewModel.CurentNameSchema;
            Assert.Equal(nameSchema, curentNameSchemaEdit);
        }

        [Fact]
        public void TestLoadProjectFunction()
        {
            SchemaWindowViewModel schemaViewModel = new SchemaWindowViewModel();
            schemaViewModel.LoadProjectXML("../../../saveProjectForTest.xml");

            int countElements = 7;
            string nameProject = "Проект тест";
            string nameSchema = "схема тест";

            int curentCountElements = schemaViewModel.CurentColectionElement.Count;
            Assert.Equal(countElements, curentCountElements);

            string curentNameProject = schemaViewModel.CurentNameProject;
            Assert.Equal(nameProject, curentNameProject);

            string curentNameSchemaList = schemaViewModel.CurentSchemaList[0].Name;
            Assert.Equal(nameSchema, curentNameSchemaList);

            string curentNameSchemaEdit = schemaViewModel.CurentNameSchema;
            Assert.Equal(nameSchema, curentNameSchemaEdit);
        }

        [Fact]
        public void TestDeleteSchemaElement()
        {
            SchemaWindowViewModel schemaViewModel = new SchemaWindowViewModel("../../../saveProjectForTest.xml");
            ElementOR? deleteElement = null;
            bool findElement = false;
            int curentcountFindElement = 0;
            foreach (ISchemaObject tempObject in schemaViewModel.CurentColectionElement)
            {
                if (tempObject is ElementOR elementOr)
                {
                    deleteElement = elementOr;
                    findElement = true;
                    curentcountFindElement++;
                }
            }
            Assert.Equal(findElement, true);

            int countFindElement = 1;
            Assert.Equal(countFindElement, curentcountFindElement);

            schemaViewModel.DeleteSchemaElement(deleteElement);

            int countElement = 3;
            string firstAndSecondElement = "ElementIN";
            string thirdElement = "ElementOUT";

            int curentCountElements = schemaViewModel.CurentColectionElement.Count;
            Assert.Equal(countElement, curentCountElements);

            string curentNameFirstElement = schemaViewModel.CurentColectionElement[0].GetType().Name;
            Assert.Equal(firstAndSecondElement, curentNameFirstElement);

            string curentNameSecondElement = schemaViewModel.CurentColectionElement[1].GetType().Name;
            Assert.Equal(firstAndSecondElement, curentNameSecondElement);

            string curentNameThirdElement = schemaViewModel.CurentColectionElement[2].GetType().Name;
            Assert.Equal(thirdElement, curentNameThirdElement);
        }

        [Fact]
        public void TestDeleteSchemaLine()
        {
            SchemaWindowViewModel schemaViewModel = new SchemaWindowViewModel("../../../saveProjectForTest.xml");
            int curentFindElements = 0;
            ObservableCollection<SchemaLine> colectionForDelete = new ObservableCollection<SchemaLine>();
            foreach (ISchemaObject tempObject in schemaViewModel.CurentColectionElement)
            {
                if (tempObject is SchemaLine tempLine)
                {
                    colectionForDelete.Add(tempLine);
                    curentFindElements++;
                }
            }
            if (colectionForDelete.Count != 0)
            {
                foreach (SchemaLine tempLine in colectionForDelete)
                {
                    schemaViewModel.DeleteSchemaLine(tempLine);
                }
            }
            else Assert.Fail("no lines");

            int findElements = 3;
            Assert.Equal(findElements, curentFindElements);

            string nameFirstAndSecondElements = "ElementIN";
            string nameThirdElement = "ElementOUT";
            string nameLastElement = "ElementOR";

            string curentNameFirstElement = schemaViewModel.CurentColectionElement[0].GetType().Name;
            Assert.Equal(nameFirstAndSecondElements, curentNameFirstElement);

            string curentNameSecondElement = schemaViewModel.CurentColectionElement[1].GetType().Name;
            Assert.Equal(nameFirstAndSecondElements, curentNameSecondElement);

            string curentNameThirdElement = schemaViewModel.CurentColectionElement[2].GetType().Name;
            Assert.Equal(nameThirdElement, curentNameThirdElement);

            string curentNameLastElement = schemaViewModel.CurentColectionElement[3].GetType().Name;
            Assert.Equal(nameLastElement, curentNameLastElement);
        }

        [Fact]
        public void TestDeleteSchems()
        {
            SchemaWindowViewModel schemaViewModel = new SchemaWindowViewModel("../../../saveProjectForTest.xml");
            schemaViewModel.CreateNewSchema();
            schemaViewModel.CreateNewSchema();
            schemaViewModel.CreateNewSchema();
            Schema firstForDelete = schemaViewModel.CurentSchemaList[0];
            Schema secondForDelete = schemaViewModel.CurentSchemaList[schemaViewModel.CurentSchemaList.Count - 1];

            schemaViewModel.DeleteSchema(firstForDelete);
            schemaViewModel.DeleteSchema(secondForDelete);

            int countSchems = 2;
            string nameFirstSchema = "схема 2";
            string nameSecondSchema = "схема 3";

            int curentCountSchema = schemaViewModel.CurentSchemaList.Count;
            Assert.Equal(countSchems, curentCountSchema);

            string curentNameFirstSchema = schemaViewModel.CurentSchemaList[0].Name;
            Assert.Equal(nameFirstSchema, curentNameFirstSchema);

            string curentNameSecondSchema = schemaViewModel.CurentSchemaList[1].Name;
            Assert.Equal(nameSecondSchema, curentNameSecondSchema);
        }

        [Fact]
        public void TestUpdateIndex()
        {
            SchemaWindowViewModel schemaViewModel = new SchemaWindowViewModel("../../../saveProjectForTest.xml");
            ElementOR? elementOr = null;
            foreach (ISchemaObject tempObject in schemaViewModel.CurentColectionElement)
            {
                if (tempObject is ElementOR findElement)
                {
                    elementOr = findElement;
                    break;
                }
            }
            if (elementOr != null) schemaViewModel.DeleteSchemaElement(elementOr);
            else Assert.Fail("no element");

            if (schemaViewModel.CurentColectionElement.Count != 3) Assert.Fail("error delete");

            schemaViewModel.UpdateIndexElements();

            int indexFirstElement = 0;
            int indexSecondElement = 1;
            int indexThirdElement = 2;
            string nameThirdElement = "ElementOUT";

            ISchemaElement tempElement = schemaViewModel.CurentColectionElement[0] as ISchemaElement;
            int curentIndexFirstElement = tempElement.IndexElement;
            Assert.Equal(indexFirstElement, curentIndexFirstElement);

            tempElement = schemaViewModel.CurentColectionElement[1] as ISchemaElement;
            int curentIndexSecondElement = tempElement.IndexElement;
            Assert.Equal(indexSecondElement, curentIndexSecondElement);

            tempElement = schemaViewModel.CurentColectionElement[2] as ISchemaElement;
            int curentIndexThirdElement = tempElement.IndexElement;
            string curentNameThirdElement = tempElement.GetType().Name;
            Assert.Equal(indexThirdElement, curentIndexThirdElement);
            Assert.Equal(nameThirdElement, curentNameThirdElement);
        }
    }
}