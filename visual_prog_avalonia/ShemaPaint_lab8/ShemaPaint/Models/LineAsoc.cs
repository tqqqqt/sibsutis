using Avalonia.Media;

namespace ShemaPaint.Models
{
    public class LineAsoc : ILines
    {
        private readonly string pathFill = "Transparent";
        private readonly string needPathData = " l -20,-20 l 20,20 l -20,20 z";
        private readonly string needLineType = "Acos";

        public LineAsoc()
        {
            PathCommands = needPathData;
            LineType = needLineType;
            PathPoints = Geometry.Parse("m 0,0 z");
            FillColor = SolidColorBrush.Parse(pathFill);
        }
    }
}
