using System;

namespace SchematicEditor.Models
{
    public class ChangeStartPointEventArgs : EventArgs
    {
        public Avalonia.Point OldStartPoint { get; set; }

        public Avalonia.Point NewStartPoint { get; set; }
    }
}
