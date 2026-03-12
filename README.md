# 🎵 MP3 Tag Reader & Editor (C Project)

---

# 📘 Project Overview

**MP3 Tag Reader & Editor** is a command-line application written in **C programming language** that allows users to **read and modify ID3v2 metadata tags in MP3 files**.

The program safely edits metadata fields such as **title, artist, album, year, genre, and comments** while preserving the original audio data.

This project demonstrates important **system programming concepts** such as:

* Binary file handling
* Parsing structured data (ID3 frames)
* Memory manipulation
* Safe file modification using temporary files
* Command-line argument processing

---

# ✨ Features

🔍 Read ID3v2 metadata from MP3 files\
📄 Display tag information in structured format\
✏️ Edit individual metadata tags\
🛡 Preserve original audio data while editing\
📂 Temporary file creation during modifications\
⚙️ Command-line interface with input validation

---

# 🧪 Demo

## View MP3 Metadata

```bash
./mp3_tag_editor -v sample.mp3
```

Example Output:

```
Title   : Example Song
Artist  : Example Artist
Album   : Example Album
Year    : 2024
Genre   : Pop
Comment : Sample Comment
```

---

## Edit MP3 Metadata

```bash
./mp3_tag_editor -e <option> <new_value> <mp3_file>
```

Example:

```bash
./mp3_tag_editor -e -t "New Song Title" sample.mp3
```

---

## Help Menu

```bash
./mp3_tag_editor --help
```

---

# 🏷 Supported ID3 Tags

| Frame ID | Tag Description |
| -------- | --------------- |
| **TIT2** | Song Title      |
| **TPE1** | Artist Name     |
| **TALB** | Album Name      |
| **TYER** | Year            |
| **TCON** | Genre           |
| **COMM** | Comment         |

---

# ⚙️ How to Compile and Run

## Compile the Program

```bash
gcc *.c -o mp3_tag_editor
```

## Run the Program

```bash
./mp3_tag_editor
```

---

# 📁 Project Structure

```
MP3_Tag_Reader_Editor
│
├── main.c        # Program entry point
├── mp3.h         # Structure definitions and declarations
├── view.c        # Metadata viewing functionality
├── edit.c        # Metadata editing functionality
├── utils.c       # Helper functions
└── README.md     # Project documentation
```

---

# 🧠 Concept Behind ID3 Metadata

MP3 files store metadata using **ID3 tags**.
Each tag contains **frames** that represent different information fields.

Example structure:

```
ID3 Header
│
├── TIT2 → Title
├── TPE1 → Artist
├── TALB → Album
├── TYER → Year
├── TCON → Genre
└── COMM → Comment
```

This project reads and modifies these **frames without altering the MP3 audio stream**.

---

# 📚 Learning Outcomes

Through this project I gained practical experience with:

* Binary file parsing in C
* Working with structured metadata formats
* Safe file modification techniques
* Command-line argument parsing
* Modular C programming

---

# 🔮 Future Improvements

* Add **album artwork editing**
* Support **ID3v1 tags**
* Implement **batch editing of multiple files**
* Add **GUI interface**

---

# 👨‍💻 Author

**Ajinkya Subhash Kadam**\
Electronics & Computer Engineering\
Embedded & System Programming Enthusiast

🔗 LinkedIn
https://www.linkedin.com/in/ajinkya-kadam-54a51b283

---

# ⭐ Support

If you found this project useful:

⭐ Star this repository on GitHub
📢 Share it with others interested in **system programming and C development**
