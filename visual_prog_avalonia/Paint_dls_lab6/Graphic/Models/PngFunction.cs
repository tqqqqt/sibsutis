using Avalonia;
using Avalonia.Controls;
using Avalonia.Media.Imaging;

namespace Graphic.Models
{
    public class PngFunction
    {
        public PngFunction() { }

        public void PngSave(string path, ItemsControl canvas)
        {
            var pixelSize = new PixelSize((int)canvas.Width, (int)canvas.Height);
            var size = new Size(canvas.Width, canvas.Height);
            using (RenderTargetBitmap bitmap = new RenderTargetBitmap(pixelSize, new Vector(96, 96)))
            {
                canvas.Measure(size);
                canvas.Arrange(new Rect(size));
                bitmap.Render(canvas);
                bitmap.Save(path);
            }
        }
    }
}
