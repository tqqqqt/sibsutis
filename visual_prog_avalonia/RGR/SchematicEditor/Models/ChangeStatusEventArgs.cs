using System;

namespace SchematicEditor.Models
{
    public class ChangeStatusEventArgs : EventArgs
    {
        public int NewStatus { get; set; }
        public int NewStatus2 { get; set; }
    }
}
