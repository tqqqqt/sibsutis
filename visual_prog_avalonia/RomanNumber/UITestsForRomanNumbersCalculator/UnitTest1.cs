using Avalonia.Controls;
using Avalonia.VisualTree;

namespace UITestsForRomanNumbersCalculator
{
    public class UnitTest1
    {
        [Fact]
        public async void Test1()
        {
            var app = AvaloniaApp.GetApp();
            var MainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(200);

            //1 - 7 tests -> button number test
            //8 test -> oper test without number
            //9 - 12 tests -> button operation test
            //13 - 16 tests -> test operation on result
            //17 test -> test for '#ERROR'

            //test 1
            string need_text = "I";
            var button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addI");
            var button_clear = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "CE");
            var box = MainWindow.GetVisualDescendants().OfType<TextBlock>().First();

            button.Command.Execute(button.CommandParameter);
            await Task.Delay(100);
            var box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "Press button 'I' but string in textBlock != 'I' ");

            //test 2
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addV");
            need_text = "V";

            button.Command.Execute(button.CommandParameter);
            await Task.Delay(100);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "Press button 'V' but string in textBlock != 'V' ");

            //test 3
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addX");
            need_text = "X";

            button.Command.Execute(button.CommandParameter);
            await Task.Delay(100);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "Press button 'X' but string in textBlock != 'X' ");

            //test 4
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addL");
            need_text = "L";

            button.Command.Execute(button.CommandParameter);
            await Task.Delay(100);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "Press button 'L' but string in textBlock != 'L' ");

            //test 5
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addC");
            need_text = "C";

            button.Command.Execute(button.CommandParameter);
            await Task.Delay(100);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "Press button 'C' but string in textBlock != 'C' ");

            //test 6
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addD");
            need_text = "D";

            button.Command.Execute(button.CommandParameter);
            await Task.Delay(100);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "Press button 'D' but string in textBlock != 'D' ");

            //test 7
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addM");
            need_text = "M";

            button.Command.Execute(button.CommandParameter);
            await Task.Delay(100);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "Press button 'M' but string in textBlock != 'M' ");

            //test 8
            button_clear.Command.Execute(button_clear.CommandParameter);
            need_text = "";
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addPL");
            button.Command.Execute(button.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addSU");
            button.Command.Execute(button.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addMU");
            button.Command.Execute(button.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addDI");
            button.Command.Execute(button.CommandParameter);


            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "Press operation button without number and string in textBlock != '' ");

            //test 9
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addPL");
            var button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addI");
            need_text = "I+I";

            button2.Command.Execute(button2.CommandParameter);
            button.Command.Execute(button.CommandParameter);
            button2.Command.Execute(button2.CommandParameter);

            await Task.Delay(100);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "String in textBlock != 'I+I' ");

            //test 10
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addSU");
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addV");
            need_text = "V-V";

            button2.Command.Execute(button2.CommandParameter);
            button.Command.Execute(button.CommandParameter);
            button2.Command.Execute(button2.CommandParameter);

            await Task.Delay(100);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "String in textBlock != 'V-V' ");

            //test 11
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addMU");
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addX");
            need_text = "X*X";

            button2.Command.Execute(button2.CommandParameter);
            button.Command.Execute(button.CommandParameter);
            button2.Command.Execute(button2.CommandParameter);

            await Task.Delay(100);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "String in textBlock != 'X*X' ");

            //test 12
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addDI");
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addL");
            need_text = "L/L";

            button2.Command.Execute(button2.CommandParameter);
            button.Command.Execute(button.CommandParameter);
            button2.Command.Execute(button2.CommandParameter);

            await Task.Delay(100);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "String in textBlock != 'L/L' ");

            //test 13
            //
            var button_res = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "res");
            //

            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addPL");
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addI");
            need_text = "XIV";

            button2.Command.Execute(button2.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addX");
            button2.Command.Execute(button2.CommandParameter);
            button.Command.Execute(button.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addV");
            button2.Command.Execute(button2.CommandParameter);
            button_res.Command.Execute(button_res.CommandParameter);

            await Task.Delay(200);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "IX+V = XIV but string in textBlock != 'XIV' ");

            //test 14
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addSU");
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addX");
            need_text = "IX";

            button2.Command.Execute(button2.CommandParameter);
            button.Command.Execute(button.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addI");
            button2.Command.Execute(button2.CommandParameter);
            button_res.Command.Execute(button_res.CommandParameter);

            await Task.Delay(200);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "X-I=IX but string in textBlock != 'IX' ");

            //test 15
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addMU");
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addV");
            need_text = "XLVIII";

            button2.Command.Execute(button2.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addI");
            button2.Command.Execute(button2.CommandParameter);
            button.Command.Execute(button.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addV");
            button2.Command.Execute(button2.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addI");
            button2.Command.Execute(button2.CommandParameter);
            button2.Command.Execute(button2.CommandParameter);
            button2.Command.Execute(button2.CommandParameter);
            button_res.Command.Execute(button_res.CommandParameter);

            await Task.Delay(200);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "VI*VIII=XLVIII but string in textBlock != 'XLVIII' ");

            //test 16
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addDI");
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addC");
            need_text = "XXXVI";

            button2.Command.Execute(button2.CommandParameter);
            button2.Command.Execute(button2.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addX");
            button2.Command.Execute(button2.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addV");
            button2.Command.Execute(button2.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addI");
            button2.Command.Execute(button2.CommandParameter);
            button.Command.Execute(button.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addV");
            button2.Command.Execute(button2.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addI");
            button2.Command.Execute(button2.CommandParameter);
            button_res.Command.Execute(button_res.CommandParameter);

            await Task.Delay(200);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "CCXVI/VI=XXXVI but string in textBlock != 'XLVIII' ");

            //test 17
            button_clear.Command.Execute(button_clear.CommandParameter);
            button = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addMU");
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addM");
            need_text = "#ERROR";

            button2.Command.Execute(button2.CommandParameter);
            button2.Command.Execute(button2.CommandParameter);
            button2.Command.Execute(button2.CommandParameter);
            button.Command.Execute(button.CommandParameter);
            button2 = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "addV");
            button2.Command.Execute(button2.CommandParameter);
            button_res.Command.Execute(button_res.CommandParameter);

            await Task.Delay(200);
            box_text = box.Text;
            Assert.True(box_text.Equals(need_text), "MMM*V>4000 but string in textBlock != '#ERROR' ");
        }
    }
}