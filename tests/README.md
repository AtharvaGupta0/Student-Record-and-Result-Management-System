# Sample session

This folder contains one scripted run of the program:

- `sample_input.txt` - the keystrokes for the session
- `sample_output.txt` - the output produced by those keystrokes

The session adds two students (one with an invalid SGPA that is rejected and
re-entered), searches by name prefix, calculates a CGPA, runs the academic
advisor, and displays the records sorted by name.

## What the sample shows

| Menu choice | Action |
|---|---|
| 1 | Add Alice Johnson (1st year, semester 1, SGPA 8.50) |
| 1 | Add Rohan Kumar (2nd year, semester 3), rejecting SGPA 11 |
| 2 -> 2 | Search for `roh` (case-insensitive prefix) |
| 4 | CGPA of Alice Johnson |
| 6 | Advisor for Rohan Kumar (CGPA 7.50, Good) |
| 9 | Records sorted by name |
| 10 | Exit |

## Reproducing the output

Run from an **empty temporary directory**. The program opens
`DataFiles/students.dat` relative to the current directory, so running this in
the project root would change the shipped data file.

```bash
REPO=/path/to/Student-Record-and-Result-Management-System
rm -rf /tmp/srms_sample && mkdir -p /tmp/srms_sample/DataFiles
cd /tmp/srms_sample
"$REPO/Executables/Student-Record-and-Management-System" \
  < "$REPO/tests/sample_input.txt" \
  | perl -pe 's/\e\[2J\e\[H/\n/g' > /tmp/srms_sample_actual.txt
diff -u "$REPO/tests/sample_output.txt" /tmp/srms_sample_actual.txt
```

`diff` prints nothing when the output matches.

On Windows, the `.exe` accepts the same input, but the command above uses a
Unix shell. Run it from WSL or Git Bash if you want to reproduce the diff.

## Notes

- The program clears the screen with ANSI escape codes. Those sequences were
  replaced with a line break in `sample_output.txt` so the file is readable.
- When input is piped from a file, the terminal does not echo the typed text,
  so several prompts appear on one line. Running interactively shows the same
  session with your typing visible.
- The SGPA values are stored per semester in a binary data file, so the sample
  always starts from an empty directory.
