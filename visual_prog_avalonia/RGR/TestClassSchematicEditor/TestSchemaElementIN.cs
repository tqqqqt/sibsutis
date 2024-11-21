using SchematicEditor.Models;

namespace TestClassSchematicEditor
{
    public class TestSchemaElementIN
    {
        [Fact]
        public void TestDoubleChangeStatus()
        {
            ElementIN elementIN = new ElementIN();

            int status = 0;

            int curentStatus = elementIN.Status;
            Assert.Equal(status, curentStatus);

            elementIN.ChangeInStatus();

            status = 1;
            curentStatus = elementIN.Status;
            Assert.Equal(status, curentStatus);
        }
    }
}
