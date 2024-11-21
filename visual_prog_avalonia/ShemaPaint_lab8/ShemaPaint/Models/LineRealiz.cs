using Avalonia.Media;

namespace ShemaPaint.Models
{
    public class LineRealiz : ILines
    {
        private readonly string pathFill = "White";
        private readonly string needPathData = " l -20,-20 l 0,40 l 20,-20 z";
        private readonly string needLineType = "Realiz";

        public LineRealiz()
        {
            PathCommands = needPathData;
            LineType = needLineType;
            PathPoints = Geometry.Parse("m 0,0 z");
            FillColor = SolidColorBrush.Parse(pathFill);
        }
    }
}
