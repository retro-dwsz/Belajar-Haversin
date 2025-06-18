/* Misc.cs */

using System.Text;

namespace Misc;

/// <summary>
/// Provides utility methods for string manipulation and console formatting.
/// Includes functions to repeat strings, center text in the terminal, and more.
/// </summary>
public static class Misc
{
    /// <summary>
    /// Gets the current width of the console window.
    /// Can be used as a reference for aligning or centering output.
    /// </summary>
    public static int TerminalSize = Console.WindowWidth;

    /// <summary>
    /// Repeats a given string or character a specified number of times.
    /// Or in other words, mimics the string multiplication from Python in C# 
    /// </summary> 
    /// <param name="str">The string or character to repeat.</param>
    /// <param name="repetitions">Number of times to repeat (default: 1).</param>
    /// <returns>A single string with the input repeated.</returns>
    /// <example>
    /// <code>
    /// string result = Misc.Repeater("hello", 3); // Returns "hellohellohello"
    /// </code>
    public static string Repeater(object str, int repetitions = 1)
    {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < repetitions; i++)
        {
            sb.Append(str?.ToString());
        }

        return sb.ToString();
    }

    /// <summary>
    /// Centers a given text within the terminal window, bordered by a repeating character.
    /// Useful for creating headers or separators in console applications.
    /// </summary>
    /// <param name="Text">The text to center (default: "Hello").</param>
    /// <param name="Char">Character used to fill borders (default: '=').</param>
    /// <param name="offset">Adds extra space to simulate padding or margin (default: 2).</param>
    /// <param name="Printing">If true, prints the result to the console (default: false).</param>
    /// <returns>The formatted centered string.</returns>
    /// <example>
    /// <code>
    /// Misc.PrintMid("Welcome", '-', offset: 4, Printing: true);
    /// // Output:
    /// // ------------------[Welcome]-------------------
    /// </code>
    /// </example>
    public static string PrintMid(string Text = "Hello", char Char = '=', int offset = 2, char LeftBorder = '[', char RightBorder = ']', bool Printing = false)
    {
        int ConsoleWidth = TerminalSize + offset;               // Get width + offset
        int Border_sz = (ConsoleWidth - Text.Length - 4) / 2;   // Subtract the length of the text and some spacing ([Text] takes up 4 characters).
                                                                // Divide the remaining space equally between left and right borders.
                                                                // If ConsoleWidth = 80, Text.Length = 5 → Remaining space = 80 - 5 - 4 = 71
                                                                // Each border gets 71 / 2 = 35 characters.

        // Build Left & Right borders
        string Left = Repeater(Char, Border_sz);                        // Left side uses exactly Border_sz characters.
        string Right = Repeater(Char, Border_sz + (Text.Length % 2));   // Right side adjusts if the text has an odd number of characters,
                                                                        // so total width stays balanced.

        // Final assembly
        string Content = $"{Left}{LeftBorder}{Text}{RightBorder}{Right}";

        if (Printing)
        {
            Console.WriteLine(Content);
        }

        return Content;
    }
}

class ColorTx
{
    public enum Position { Back, Fore }

    public static string ColorStr(string text = "Hello, world!", uint hex=0xFF109696, Position pos = Position.Fore)
    {
        // Parse RGB from 0xAARRGGBB or 0xRRGGBB
        byte a = 255, r, g, b;
        if (hex > 0xFFFFFF)
        {
            a = (byte)((hex >> 24) & 0xFF);
            r = (byte)((hex >> 16) & 0xFF);
            g = (byte)((hex >> 8) & 0xFF);
            b = (byte)(hex & 0xFF);
        }
        else
        {
            r = (byte)((hex >> 16) & 0xFF);
            g = (byte)((hex >> 8) & 0xFF);
            b = (byte)(hex & 0xFF);
        }

        // Convert RGB to closest ConsoleColor
        ConsoleColor color = RgbToConsoleColor(r, g, b);

        if (pos == Position.Fore)
            Console.ForegroundColor = color;
        else
            Console.BackgroundColor = color;

        return text;
    }

    public static void Print(uint hex, Position pos, string text)
    {
        Console.WriteLine(ColorStr(text, hex, pos));
        Console.ResetColor(); // Don't leave your terminal cursed
    }

    // Kinda not useful
    public static void Debug(string text)
    {
        Console.Write("DEBUG RAW: ");
        foreach (char c in text)
        {
            if (!char.IsControl(c) && !char.IsWhiteSpace(c))
            {
                Console.Write(c);
            }
            else
            {
                Console.Write($"\\x{((int)c):X2}");
            }
        }
        Console.WriteLine();
    }

    private static ConsoleColor RgbToConsoleColor(byte r, byte g, byte b)
    {
        // Naive RGB -> ConsoleColor mapping
        int index = (r > 128 ? 4 : 0) + (g > 128 ? 2 : 0) + (b > 128 ? 1 : 0);
        return (ConsoleColor)index;
    }
}



/* End Misc.cs */