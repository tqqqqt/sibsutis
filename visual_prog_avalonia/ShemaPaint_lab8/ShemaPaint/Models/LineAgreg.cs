using Avalonia.Media;

namespace ShemaPaint.Models
{
    public class LineAgreg : ILines
    {
        private readonly string pathFill = "White";
        private readonly string needPathData = " l -20,-20 l -20,20 l 20,20 l 20,-20 z";
        private readonly string needLineType = "Agreg";

        public LineAgreg()
        {
            PathCommands = needPathData;
            LineType = needLineType;
            PathPoints = Geometry.Parse("m 0,0 z");
            FillColor = SolidColorBrush.Parse(pathFill);
        }
    }
}
