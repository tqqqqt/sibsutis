using Avalonia.Controls;
using Avalonia.Media;
using Avalonia.VisualTree;
using System.Drawing;

namespace UITestsStudent
{
    public class UnitTest1
    {
        [Fact]
        public async Task Test1Async()
        {

            // 1 test - add button
            // 2 test - delete button
            // 3 test - save and load test
            // 4 test - colors test

            var app = AvaloniaApp.GetApp();
            var MainWindow = AvaloniaApp.GetMainWindow();
            await Task.Delay(200);

            var button_add = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "b_add");
            var button_del = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "b_del");
            var button_save = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "b_save");
            var button_load = MainWindow.GetVisualDescendants().OfType<Button>().First(b => b.Name == "b_load");

            var textbox_s1 = MainWindow.GetVisualDescendants().OfType<TextBlock>().First(b => b.Name == "text_sr1");
            var textbox_s2 = MainWindow.GetVisualDescendants().OfType<TextBlock>().First(b => b.Name == "text_sr2");
            var textbox_s3 = MainWindow.GetVisualDescendants().OfType<TextBlock>().First(b => b.Name == "text_sr3");
            var textbox_s4 = MainWindow.GetVisualDescendants().OfType<TextBlock>().First(b => b.Name == "text_sr4");
            var textbox_s5 = MainWindow.GetVisualDescendants().OfType<TextBlock>().First(b => b.Name == "text_sr5");
            var textbox_s6 = MainWindow.GetVisualDescendants().OfType<TextBlock>().First(b => b.Name == "text_sr6");

            var combox_text = MainWindow.GetVisualDescendants().OfType<TextBox>().First(b => b.Name == "Sel");
            var combox_1 = MainWindow.GetVisualDescendants().OfType<ComboBox>().First(b => b.Name == "Sel1");
            var combox_2 = MainWindow.GetVisualDescendants().OfType<ComboBox>().First(b => b.Name == "Sel2");
            var combox_3 = MainWindow.GetVisualDescendants().OfType<ComboBox>().First(b => b.Name == "Sel3");
            var combox_4 = MainWindow.GetVisualDescendants().OfType<ComboBox>().First(b => b.Name == "Sel4");
            var combox_5 = MainWindow.GetVisualDescendants().OfType<ComboBox>().First(b => b.Name == "Sel5");

            var listbox = MainWindow.GetVisualDescendants().OfType<ListBox>().First(b => b.Name == "listbox");

            var textbox_text = textbox_s1.Text;
            var textbox_color = (textbox_s1.Background as SolidColorBrush).Color;

            button_save.Command.Execute(button_save.CommandParameter);
            await Task.Delay(50);


            // test 1 - added item
            combox_text.Text = "Андрей";
            combox_1.SelectedIndex = 1;
            combox_2.SelectedIndex = 2;
            combox_3.SelectedIndex = 2;
            combox_4.SelectedIndex = 3;
            combox_5.SelectedIndex = 3;
            button_add.Command.Execute(button_add.CommandParameter);

            await Task.Delay(100);
            textbox_text = textbox_s1.Text;
            string need_text = "1";
            Assert.True(textbox_text.Equals(need_text), " After add sred znach_1 != '1'");

            textbox_text = textbox_s2.Text;
            need_text = "1,33";
            Assert.True(textbox_text.Equals(need_text), " After add sred znach_2 != '1,33'");

            textbox_text = textbox_s3.Text;
            need_text = "1,33";
            Assert.True(textbox_text.Equals(need_text), " After add sred znach_3 != '1,33'");

            textbox_text = textbox_s4.Text;
            need_text = "2";
            Assert.True(textbox_text.Equals(need_text), " After add sred znach_4 != '1,33'");

            textbox_text = textbox_s5.Text;
            need_text = "1,33";
            Assert.True(textbox_text.Equals(need_text), " After add sred znach_5 != '1,33'");

            textbox_text = textbox_s6.Text;
            need_text = "1,47";
            Assert.True(textbox_text.Equals(need_text), " After add sred znach obshee != '1,47'");


            // test 2 - delete items
            listbox.SelectedIndex = 2;
            button_del.Command.Execute(button_del.CommandParameter);
            await Task.Delay(100);
            listbox.SelectedIndex = 0;
            button_del.Command.Execute(button_del.CommandParameter);
            await Task.Delay(100);

            textbox_text = textbox_s1.Text;
            need_text = "1";
            Assert.True(textbox_text.Equals(need_text), " After delete sred znach_1 != '1'");

            textbox_text = textbox_s2.Text;
            need_text = "2";
            Assert.True(textbox_text.Equals(need_text), " After delete sred znach_2 != '1,33'");

            textbox_text = textbox_s3.Text;
            need_text = "1";
            Assert.True(textbox_text.Equals(need_text), " After delete sred znach_3 != '1,33'");

            textbox_text = textbox_s4.Text;
            need_text = "2";
            Assert.True(textbox_text.Equals(need_text), " After delete sred znach_4 != '1,33'");

            textbox_text = textbox_s5.Text;
            need_text = "0";
            Assert.True(textbox_text.Equals(need_text), " After delete sred znach_5 != '1,33'");

            textbox_text = textbox_s6.Text;
            need_text = "1,4";
            Assert.True(textbox_text.Equals(need_text), " After delete sred znach obshee != '1,47'");


            // test 3 - save and load
            button_load.Command.Execute(button_load.CommandParameter);
            await Task.Delay(50);
            textbox_text = textbox_s1.Text;
            need_text = "1,5";
            Assert.True(textbox_text.Equals(need_text), " Error sr znach after load ");

            textbox_text = textbox_s2.Text;
            need_text = "1,5";
            Assert.True(textbox_text.Equals(need_text), " Error sr znach after load ");

            textbox_text = textbox_s3.Text;
            need_text = "1,5";
            Assert.True(textbox_text.Equals(need_text), " Error sr znach after load ");

            textbox_text = textbox_s4.Text;
            need_text = "2";
            Assert.True(textbox_text.Equals(need_text), " Error sr znach after load ");

            textbox_text = textbox_s5.Text;
            need_text = "1";
            Assert.True(textbox_text.Equals(need_text), " Error sr znach after load ");

            textbox_text = textbox_s6.Text;
            need_text = "1,6";
            Assert.True(textbox_text.Equals(need_text), " Error sr znach after load ");


            //4 test - color 
            combox_text.Text = "Андрей";
            combox_1.SelectedIndex = 1;
            combox_2.SelectedIndex = 1;
            combox_3.SelectedIndex = 3;
            combox_4.SelectedIndex = 1;
            combox_5.SelectedIndex = 1;
            button_add.Command.Execute(button_add.CommandParameter);
            await Task.Delay(50);

            textbox_color = (textbox_s1.Background as SolidColorBrush).Color;
            var need_color = Colors.Yellow;
            Assert.True(textbox_color.Equals(need_color), " Error 1 button color != 'Yellow' ");

            textbox_color = (textbox_s2.Background as SolidColorBrush).Color;
            Assert.True(textbox_color.Equals(need_color), " Error 2 button color != 'Yellow' ");

            textbox_color = (textbox_s4.Background as SolidColorBrush).Color;
            Assert.True(textbox_color.Equals(need_color), " Error 4 button color != 'Yellow' ");

            textbox_color = (textbox_s6.Background as SolidColorBrush).Color;
            Assert.True(textbox_color.Equals(need_color), " Error 6 button color != 'Yellow' ");

            textbox_color = (textbox_s3.Background as SolidColorBrush).Color;
            need_color = Colors.Green;
            Assert.True(textbox_color.Equals(need_color), " Error 1 button color != 'Yellow' ");

            textbox_color = (textbox_s5.Background as SolidColorBrush).Color;
            need_color = Colors.Red;
            Assert.True(textbox_color.Equals(need_color), " Error 1 button color != 'Yellow' ");
        }
    }
}