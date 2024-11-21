using Avalonia;
using Avalonia.Controls;
using Avalonia.Media.Imaging;

namespace ShemaPaint.Models
{
    public class PNGSaver
    {
        public void Save(ItemsControl canvas, string path)
        {
            var pixelSize = new PixelSize((int)canvas.Width, (int)canvas.Height);
            var size = new Size(canvas.Width, canvas.Height);
            using (RenderTargetBitmap bitmap = new RenderTargetBitmap(pixelSize, new Vector(96, 96)))
            {
                canvas.Measure(size);
                bitmap.Render(canvas);
                bitmap.Save(path);
            }
        }
    }
}
