using Graphic.Models;
using ReactiveUI;
using System.Collections.ObjectModel;

namespace Graphic.ViewModels.Pages
{
    public class PolyLineViewModel : ViewModelBase
    {
        private ObservableCollection<IFigure> colection;
        private string name, points;
        private int select = 0, select_figure, flag = 0;
        private double thic = 1;
        public PolyLineViewModel(ref ObservableCollection<IFigure> col)
        {
            colection = col;
            name = string.Empty;
            points = string.Empty;
        }

        // interf
        public string Name
        {
            get => name;
            set
            {
                this.RaiseAndSetIfChanged(ref name, value);
            }
        }

        public string Points
        {
            get => points;
            set
            {
                this.RaiseAndSetIfChanged(ref points, value);
            }
        }

        public double Thic
        {
            get => thic;
            set
            {
                this.RaiseAndSetIfChanged(ref thic, value);
            }
        }

        public int Select
        {
            get => select;
            set
            {
                this.RaiseAndSetIfChanged(ref select, value);
            }
        }

        // function
        public void UpdateRef(ref ObservableCollection<IFigure> figur_colection)
        {
            colection = figur_colection;
        }
        public void ChangeOption(int num)
        {
            select_figure = num;
            if (select_figure < 0) select_figure = 0;
            var figure = colection[select_figure] as Gr_PolyLine;
            Name = figure.Name;
            Points = figure.save_point;
            Thic = figure.StrokeThic;
            var color = figure.StrokeColor.ToString();
            if (color == "Black") Select = 0;
            else if (color == "Green") Select = 1;
            else if (color == "Yellow") Select = 2;
            else if (color == "Blue") Select = 3;
            else if (color == "Red") Select = 4;
            else Select = 5;
            flag = 1;
        }
        public void Button_add()
        {
            if (Points != null && Name != null)
            {
                string temp_all_point = Points;

                string color11 = string.Empty;
                if (select == 0) color11 = "Black";
                else if (select == 1) color11 = "Green";
                else if (select == 2) color11 = "Yellow";
                else if (select == 3) color11 = "Blue";
                else if (select == 4) color11 = "Red";
                else color11 = "RosyBrown";

                Gr_PolyLine polyLine = new Gr_PolyLine(Name, temp_all_point, color11, Thic);
                if (flag == 0) colection.Add(polyLine);
                else if (flag == 1)
                {
                    colection[select_figure] = polyLine;
                    flag = 0;
                    select_figure = -2;
                }
                Button_cancel();
            }
        }

        public void Button_cancel()
        {
            Name = string.Empty;
            Points = string.Empty;
            Select = 0;
            Thic = 1;
        }
    }
}
