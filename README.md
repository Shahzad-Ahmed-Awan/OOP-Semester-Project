# 🌟 C++ Lifestyle & Productivity Manager  
_A real-world, modular console application built with pure Object-Oriented Programming fundamentals in C++_

Welcome to a complete C++ console-based productivity suite designed to simulate **daily life management**, including study tracking, fitness monitoring, expense logging, habit building, and mental wellness — all built **without STL, DSA, or modern C++**, just using **pure OOP, file handling, arrays, and logic**.

> 🎯 Ideal for beginner to intermediate programmers, students, or anyone who wants to build clean, modular, and practical console applications in C++.

---

## 📚 Table of Contents

- [📌 Project Summary](#-project-summary)
- [🧩 Modules & Features](#-modules--features)
- [📂 File Organization](#-file-organization)
- [🚀 How to Compile & Run](#-how-to-compile--run)
- [🎯 Learning Objectives](#-learning-objectives)
- [📸 Screenshots (Optional)](#-screenshots-optional)
- [👨‍💻 About the Developer](#-about-the-developer)

---

## 📌 Project Summary

This project simulates a personal **Lifestyle & Productivity Management System** using only:
- 💡 **Core Object-Oriented Programming** (Classes, Inheritance, Encapsulation)
- 📁 **File Handling** (`ifstream`, `ofstream`, `fstream`)
- 🧱 **Static Arrays and Structs** (No STL)
- 🖥️ **Menu-driven console interface**

> ❌ No STL, DSA, recursion, templates, sorting/searching algorithms, or modern C++ features used.

---

## 🧩 Modules & Features

### 🔐 User Management
- User Registration & Login (with Caesar Cipher password encryption)
- Profile Update (name, age, goals)
- File: `users.txt`

### 📚 Study Tracker
- Add/Delete Tasks, Mark Complete
- Daily Summary & Streak Tracker
- Pomodoro-style 25+5 min Timer
- Files: `tasks.txt`, `streak.txt`

### 🏋️ Fitness Tracker
- BMI Calculator (with categories)
- Water Intake Tracker
- Goal Setting: Bulk / Cut / Maintain
- Files: `fitness.txt`, `water.txt`

### 💰 Finance Manager
- Add Daily Expenses
- Monthly Budget Comparison
- File: `expenses.txt`

### 📅 Habits & Hobbies
- Create & Check-in Daily Habits
- Hobby Planner (date & time based)
- Streak Counter
- Files: `habits.txt`, `hobbies.txt`

### 🧠 Mental Wellness
- Random Motivational Quotes
- 5-10 min Break Timer
- Mind Exercises (riddles, breathing tips)
- Files: `quotes.txt`, `exercises.txt`

---

## 📂 File Organization

```
/LifestyleManager/
│
├── main.cpp
├── UserManager.h/.cpp
├── StudySection.h/.cpp
├── FitnessTracker.h/.cpp
├── FinanceManager.h/.cpp
├── HabitManager.h/.cpp
├── WellnessSection.h/.cpp
├── Utils.h/.cpp
│
└── /data/
    ├── users.txt
    ├── tasks.txt
    ├── streak.txt
    ├── fitness.txt
    ├── water.txt
    ├── expenses.txt
    ├── budget.txt
    ├── habits.txt
    ├── hobbies.txt
    ├── quotes.txt
    └── exercises.txt
```

---

## 🚀 How to Compile & Run

> Make sure all `.cpp` and `.h` files are in the same folder or properly linked.

```bash
g++ main.cpp -o LifestyleManagerApp
./LifestyleManagerApp
```

📝 Tip: Use `system("cls")` and `system("pause")` for better menu navigation (on Windows).

---

## 🎯 Learning Objectives

- ✅ Apply Object-Oriented Programming in real-life scenarios
- ✅ Work with file storage using `fstream`
- ✅ Build full-featured modular programs without STL or DSA
- ✅ Practice clean code, encapsulation, and modularity

---

## 📸 Screenshots (Optional)

> You can add screenshots or GIFs of your program running here.

---

## 👨‍💻 About the Developer

**Shahzad Ahmed Awan**  
2nd Semester Software Engineering Student  
🎯 Focused on mastering C++ and core programming logic  
💻 Passionate about building real-world console apps  
📚 Believes in "learning by doing"

🔗 [My GitHub Profile](https://github.com/Shahzad-Ahmed-Awan)

---

⭐ *If you found this helpful, don't forget to star the repo and share it with your friends!*
