using Avalonia.Controls;
using Avalonia.Media;
using Avalonia.VisualTree;
using SchematicEditor.Views;

namespace TestSchematicEditor
{
    public class ElementButtonTests
    {
        [Fact]
        public async void TestButtonIn()
        {
            var app = AvaloniaApp.GetApp();
            var mainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(100);

            var buttonCreate = mainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonCreate");
            await Task.Delay(50);
            mainWindow.ClickCreateButton(buttonCreate, null);

            var needColor = Colors.AliceBlue;
            var schemaWindow = (SchemaWindow)app.Windows.First(b => b.Title == "RGR - Schema Window");

            var buttonIn = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonIN");
            await Task.Delay(50);
            schemaWindow.ClickElementButton(buttonIn, null);
            var curentColor = (buttonIn.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);

            needColor = Colors.White;
            schemaWindow.ClickElementButton(buttonIn, null);
            curentColor = (buttonIn.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);
        }

        [Fact]
        public async void TestButtonOut()
        {
            var app = AvaloniaApp.GetApp();
            var mainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(100);

            var buttonCreate = mainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonCreate");
            await Task.Delay(50);
            mainWindow.ClickCreateButton(buttonCreate, null);

            var needColor = Colors.AliceBlue;
            var schemaWindow = (SchemaWindow)app.Windows.First(b => b.Title == "RGR - Schema Window");
            var buttonOut = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonOUT");
            await Task.Delay(50);

            schemaWindow.ClickElementButton(buttonOut, null);
            var curentColor = (buttonOut.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);

            needColor = Colors.White;
            schemaWindow.ClickElementButton(buttonOut, null);
            curentColor = (buttonOut.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);
        }

        [Fact]
        public async void TestButtonAnd()
        {
            var app = AvaloniaApp.GetApp();
            var mainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(100);

            var buttonCreate = mainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonCreate");
            await Task.Delay(50);
            mainWindow.ClickCreateButton(buttonCreate, null);

            var needColor = Colors.AliceBlue;
            var schemaWindow = (SchemaWindow)app.Windows.First(b => b.Title == "RGR - Schema Window");
            var buttonAnd = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonAND");
            await Task.Delay(50);

            schemaWindow.ClickElementButton(buttonAnd, null);
            var curentColor = (buttonAnd.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);

            needColor = Colors.White;
            schemaWindow.ClickElementButton(buttonAnd, null);
            curentColor = (buttonAnd.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);
        }

        [Fact]
        public async void TestButtonOr()
        {
            var app = AvaloniaApp.GetApp();
            var mainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(100);

            var buttonCreate = mainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonCreate");
            await Task.Delay(50);
            mainWindow.ClickCreateButton(buttonCreate, null);

            var needColor = Colors.AliceBlue;
            var schemaWindow = (SchemaWindow)app.Windows.First(b => b.Title == "RGR - Schema Window");
            var buttonOr = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonOR");
            await Task.Delay(50);

            schemaWindow.ClickElementButton(buttonOr, null);
            var curentColor = (buttonOr.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);

            needColor = Colors.White;
            schemaWindow.ClickElementButton(buttonOr, null);
            curentColor = (buttonOr.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);
        }

        [Fact]
        public async void TestButtonNo()
        {
            var app = AvaloniaApp.GetApp();
            var mainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(100);

            var buttonCreate = mainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonCreate");
            await Task.Delay(50);
            mainWindow.ClickCreateButton(buttonCreate, null);

            var needColor = Colors.AliceBlue;
            var schemaWindow = (SchemaWindow)app.Windows.First(b => b.Title == "RGR - Schema Window");
            var buttonNo = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonNO");
            await Task.Delay(50);

            schemaWindow.ClickElementButton(buttonNo, null);
            var curentColor = (buttonNo.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);

            needColor = Colors.White;
            schemaWindow.ClickElementButton(buttonNo, null);
            curentColor = (buttonNo.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);
        }

        [Fact]
        public async void TestButtonXor()
        {
            var app = AvaloniaApp.GetApp();
            var mainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(100);

            var buttonCreate = mainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonCreate");
            await Task.Delay(50);
            mainWindow.ClickCreateButton(buttonCreate, null);

            var needColor = Colors.AliceBlue;
            var schemaWindow = (SchemaWindow)app.Windows.First(b => b.Title == "RGR - Schema Window");
            var buttonXor = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonXOR");
            await Task.Delay(50);

            schemaWindow.ClickElementButton(buttonXor, null);
            var curentColor = (buttonXor.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);

            needColor = Colors.White;
            schemaWindow.ClickElementButton(buttonXor, null);
            curentColor = (buttonXor.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);
        }

        [Fact]
        public async void TestButtonDe()
        {
            var app = AvaloniaApp.GetApp();
            var mainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(100);

            var buttonCreate = mainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonCreate");
            await Task.Delay(50);
            mainWindow.ClickCreateButton(buttonCreate, null);

            var needColor = Colors.AliceBlue;
            var schemaWindow = (SchemaWindow)app.Windows.First(b => b.Title == "RGR - Schema Window");
            var buttonDe = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonDE");
            await Task.Delay(50);

            schemaWindow.ClickElementButton(buttonDe, null);
            var curentColor = (buttonDe.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);

            needColor = Colors.White;
            schemaWindow.ClickElementButton(buttonDe, null);
            curentColor = (buttonDe.Background as SolidColorBrush).Color;
            Assert.Equal(needColor, curentColor);
        }

        [Fact]
        public async void TestButtonAll()
        {
            var app = AvaloniaApp.GetApp();
            var mainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(100);

            var buttonCreate = mainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonCreate");
            await Task.Delay(50);
            mainWindow.ClickCreateButton(buttonCreate, null);

            var schemaWindow = (SchemaWindow)app.Windows.First(b => b.Title == "RGR - Schema Window");
            var buttonIn = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonIN");
            var buttonOut = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonOUT");
            var buttonAnd = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonAND");
            var buttonOr = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonOR");
            var buttonNo = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonNO");
            var buttonXor = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonXOR");
            var buttonDe = schemaWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "buttonDE");
            await Task.Delay(50);

            var needColorBlue = Colors.AliceBlue;
            var needColorWhite = Colors.White;

            schemaWindow.ClickElementButton(buttonIn, null);
            var curentColor = (buttonIn.Background as SolidColorBrush).Color;
            Assert.Equal(needColorBlue, curentColor);
            schemaWindow.ClickElementButton(buttonOut, null);
            curentColor = (buttonIn.Background as SolidColorBrush).Color;
            Assert.Equal(needColorWhite, curentColor);
            curentColor = (buttonOut.Background as SolidColorBrush).Color;
            Assert.Equal(needColorBlue, curentColor);
            schemaWindow.ClickElementButton(buttonAnd, null);
            curentColor = (buttonOut.Background as SolidColorBrush).Color;
            Assert.Equal(needColorWhite, curentColor);
            curentColor = (buttonAnd.Background as SolidColorBrush).Color;
            Assert.Equal(needColorBlue, curentColor);
            schemaWindow.ClickElementButton(buttonOr, null);
            curentColor = (buttonAnd.Background as SolidColorBrush).Color;
            Assert.Equal(needColorWhite, curentColor);
            curentColor = (buttonOr.Background as SolidColorBrush).Color;
            Assert.Equal(needColorBlue, curentColor);
            schemaWindow.ClickElementButton(buttonNo, null);
            curentColor = (buttonOr.Background as SolidColorBrush).Color;
            Assert.Equal(needColorWhite, curentColor);
            curentColor = (buttonNo.Background as SolidColorBrush).Color;
            Assert.Equal(needColorBlue, curentColor);
            schemaWindow.ClickElementButton(buttonXor, null);
            curentColor = (buttonNo.Background as SolidColorBrush).Color;
            Assert.Equal(needColorWhite, curentColor);
            curentColor = (buttonXor.Background as SolidColorBrush).Color;
            Assert.Equal(needColorBlue, curentColor);
            schemaWindow.ClickElementButton(buttonDe, null);
            curentColor = (buttonXor.Background as SolidColorBrush).Color;
            Assert.Equal(needColorWhite, curentColor);
            curentColor = (buttonDe.Background as SolidColorBrush).Color;
            Assert.Equal(needColorBlue, curentColor);
            schemaWindow.ClickElementButton(buttonDe, null);
            curentColor = (buttonDe.Background as SolidColorBrush).Color;
            Assert.Equal(needColorWhite, curentColor);
        }
    }
}