using Avalonia.Media;

namespace ShemaPaint.Models
{
    public class LineNasled : ILines
    {
        private readonly string pathFill = "White";
        private readonly string needPathData = " l -20,-20 l 0,40 l 20,-20 z";
        private readonly string needLineType = "Nasled";

        public LineNasled()
        {
            PathCommands = needPathData;
            LineType = needLineType;
            PathPoints = Geometry.Parse("m 0,0 z");
            FillColor = SolidColorBrush.Parse(pathFill);
        }
    }
}
