using Graphic.Models;
using ReactiveUI;
using System.Collections.ObjectModel;

namespace Graphic.ViewModels.Pages
{
    public class LineViewModel : ViewModelBase
    {
        private ObservableCollection<IFigure> colection;
        private string name, start_point, end_point;
        private int select, flag = 0, select_figure;
        private double thick = 1;
        private string angle = "0", rotate = "0 0", scale = "1 1", skew = "0 0";

        // constr
        public LineViewModel(ref ObservableCollection<IFigure> col)
        {
            colection = col;
            name = string.Empty;
            start_point = string.Empty;
            end_point = string.Empty;
            flag = 0;
        }

        // interf
        public string Name
        {
            get => name;
            set => this.RaiseAndSetIfChanged(ref name, value);
        }
        public string Start
        {
            get => start_point;
            set => this.RaiseAndSetIfChanged(ref start_point, value);
        }

        public string End
        {
            get => end_point;
            set => this.RaiseAndSetIfChanged(ref end_point, value);
        }
        public double Thic
        {
            get => thick;
            set => this.RaiseAndSetIfChanged(ref thick, value);
        }
        public int Select
        {
            get => select;
            set => this.RaiseAndSetIfChanged(ref select, value);
        }
        public string Angle
        {
            get => angle;
            set => this.RaiseAndSetIfChanged(ref angle, value);
        }
        public string Rotate
        {
            get => rotate;
            set => this.RaiseAndSetIfChanged(ref rotate, value);
        }
        public string Scale
        {
            get => scale;
            set => this.RaiseAndSetIfChanged(ref scale, value);
        }
        public string Skew
        {
            get => skew;
            set => this.RaiseAndSetIfChanged(ref skew, value);
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
            var figur = colection[select_figure] as Gr_Line;
            Name = figur.Name;
            Thic = figur.StrokeThic;
            Start = figur.StartPoint.X.ToString() + "," + figur.StartPoint.Y.ToString();
            End = figur.EndPoint.X.ToString() + "," + figur.EndPoint.Y.ToString();
            var color = figur.StrokeColor.ToString();
            if (color == "Black") Select = 0;
            else if (color == "Green") Select = 1;
            else if (color == "Yellow") Select = 2;
            else if (color == "Blue") Select = 3;
            else if (color == "Red") Select = 4;
            else Select = 5;
            Angle = figur.AngleRT.ToString();
            Rotate = figur.RTX.ToString() + " " + figur.RTY.ToString();
            Scale = figur.STX.ToString() + " " + figur.STY.ToString();
            Skew = figur.AngleSTX.ToString() + " " + figur.AngleSTY.ToString();
            flag = 1;
        }
        public void Button_add()
        {
            if (Start != null && End != null && Name != null)
            {
                string color11 = string.Empty;
                if (select == 0) color11 = "Black";
                else if (select == 1) color11 = "Green";
                else if (select == 2) color11 = "Yellow";
                else if (select == 3) color11 = "Blue";
                else if (select == 4) color11 = "Red";
                else color11 = "RosyBrown";

                Gr_Line line = new Gr_Line(Name, Thic, color11, Start, End);
                line.Gr_Line_transform(Angle, Rotate, Scale, Skew);
                if (flag == 0) colection.Add(line);
                else if (flag == 1)
                {
                    colection[select_figure] = line;
                    flag = 0;
                    select_figure = -2;
                }
                Button_cancel();
            }
        }

        public void Button_cancel()
        {
            Name = string.Empty;
            Start = string.Empty;
            End = string.Empty;
            Thic = 1;
            Select = 0;
            flag = 0;
            Angle = "0";
            Rotate = "0 0";
            Scale = "1 1";
            Skew = "0 0";
        }
    }
}
