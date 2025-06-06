/* Misc.cs */

using System.Text;

namespace Misc;

/// <summary>
/// Provides utility methods for string manipulation and console formatting.
/// Includes functions to repeat strings, center text in the terminal, and more.
/// </summary>
public static class Mics
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
    /// string result = Mics.Repeater("hello", 3); // Returns "hellohellohello"
    /// </code>
    public static string Repeater(dynamic str, int repetitions = 1)
    {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < repetitions; i++)
        {
            sb.Append(str);
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
    /// Mics.PrintMid("Welcome", '-', offset: 4, Printing: true);
    /// // Output:
    /// // ------------------[Welcome]-------------------
    /// </code>
    /// </example>
    public static string PrintMid(string Text = "Hello", char Char = '=', int offset = 2, bool Printing = false)
    {
        int ConsoleWidth = TerminalSize + offset;               // Get width + offset
        int Border_sz = (ConsoleWidth - Text.Length - 4) / 2;   // Subtract the length of the text and some spacing ([Text] takes up 4 characters).
                                                                // Divide the remaining space equally between left and right borders.
                                                                // If ConsoleWidth = 80, Text.Length = 5 → Remaining space = 80 - 5 - 4 = 71
                                                                // Each border gets 71 / 2 = 35 characters.

        /// Build Left & Right borders
        string Left = Repeater(Char, Border_sz);                        // Left side uses exactly Border_sz characters.
        string Right = Repeater(Char, Border_sz + (Text.Length % 2));   // Right side adjusts if the text has an odd number of characters,
                                                                        // so total width stays balanced.

        /// Final assembly
        string Content = $"{Left}[{Text}]{Right}";

        if (Printing)
        {
            Console.WriteLine(Content);
        }

        return Content;
    }
}


/* End Misc.cs */