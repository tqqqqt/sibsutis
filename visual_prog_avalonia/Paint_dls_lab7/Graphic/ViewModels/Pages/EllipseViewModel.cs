using Graphic.Models;
using ReactiveUI;
using System.Collections.ObjectModel;

namespace Graphic.ViewModels.Pages
{
    public class EllipseViewModel : ViewModelBase
    {
        private ObservableCollection<IFigure> colection;
        private string name = string.Empty, points = string.Empty;
        private int select1 = 0, select2 = 0, select_figure, flag = 0;
        private int wid = 0, hei = 0;
        private double thic = 1;
        private string angle = "0", rotate = "0 0", scale = "1 1", skew = "0 0";
        public EllipseViewModel(ref ObservableCollection<IFigure> colec)
        {
            colection = colec;
        }

        public string Name
        {
            get => name;
            set => this.RaiseAndSetIfChanged(ref name, value);
        }
        public string Points
        {
            get => points;
            set => this.RaiseAndSetIfChanged(ref points, value);
        }
        public double Thic
        {
            get => thic;
            set => this.RaiseAndSetIfChanged(ref thic, value);
        }
        public int Select1
        {
            get => select1;
            set => this.RaiseAndSetIfChanged(ref select1, value);
        }
        public int Select2
        {
            get => select2;
            set => this.RaiseAndSetIfChanged(ref select2, value);
        }
        public int Wid
        {
            get => wid;
            set => this.RaiseAndSetIfChanged(ref wid, value);
        }
        public int Hei
        {
            get => hei;
            set => this.RaiseAndSetIfChanged(ref hei, value);
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
            var figure = colection[select_figure] as Gr_Ellipse;
            Name = figure.Name;
            Points = figure.StartPoint.X.ToString() + "," + figure.StartPoint.Y.ToString();
            Wid = figure.Width;
            Hei = figure.Height;
            Thic = figure.StrokeThic;
            var color1 = figure.StrokeColor.ToString();
            var color2 = figure.Fill.ToString();
            if (color1 == "Black") Select1 = 0;
            else if (color1 == "Green") Select1 = 1;
            else if (color1 == "Yellow") Select1 = 2;
            else if (color1 == "Blue") Select1 = 3;
            else if (color1 == "Red") Select1 = 4;
            else Select1 = 5;
            if (color2 == "Black") Select2 = 0;
            else if (color2 == "Green") Select2 = 1;
            else if (color2 == "Yellow") Select2 = 2;
            else if (color2 == "Blue") Select2 = 3;
            else if (color2 == "Red") Select2 = 4;
            else Select2 = 5;
            Angle = figure.AngleRT.ToString();
            Rotate = figure.RTX.ToString() + " " + figure.RTY.ToString();
            Scale = figure.STX.ToString() + " " + figure.STY.ToString();
            Skew = figure.AngleSTX.ToString() + " " + figure.AngleSTY.ToString();
            flag = 1;
        }
        public void Button_add()
        {
            if (Points != null && Name != null)
            {
                string color11 = string.Empty, color22 = string.Empty;
                if (select1 == 0) color11 = "Black";
                else if (select1 == 1) color11 = "Green";
                else if (select1 == 2) color11 = "Yellow";
                else if (select1 == 3) color11 = "Blue";
                else if (select1 == 4) color11 = "Red";
                else color11 = "RosyBrown";

                if (select2 == 0) color22 = "Black";
                else if (select2 == 1) color22 = "Green";
                else if (select2 == 2) color22 = "Yellow";
                else if (select2 == 3) color22 = "Blue";
                else if (select2 == 4) color22 = "Red";
                else color22 = "RosyBrown";

                Gr_Ellipse ellipse = new Gr_Ellipse(Name, Wid, Hei, Points, color11, Thic, color22);
                ellipse.Gr_Ellipse_transform(Angle, Rotate, Scale, Skew);
                if (flag == 0) colection.Add(ellipse);
                else if (flag == 1)
                {
                    colection[select_figure] = ellipse;
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
            Select1 = 0;
            Select2 = 0;
            Thic = 1;
            Wid = 1;
            Hei = 1;
            Angle = "0";
            Rotate = "0 0";
            Scale = "1 1";
            Skew = "0 0";
        }
    }
}
