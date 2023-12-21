# TopFrequentWords
A simple app that generates top N frequent words.

In the code N is set to 15.
The words are displayed in the form of a bar chart.
The user can control processing with the "cancel" button.

**Working principle:**
A user selects a txt file. The file is processed in WordsFrequencyAnalyzer. 
This processing is in a separate thread.
Since we can't listen to signals from the working thread, there is a wrapper class called "AnalyzerListener" in *ver1* and "Controller" in *ver2*.

The wrapper class redirects emitted signals to the GUI thread.


In **ver1** a thread is created in a *main.cpp* and the working object is sent there, while in **ver2**  the working thread is a member variable of the *Controller* class.

<img width="960" alt="Appbar" src="https://github.com/sakesfar/TopFrequentWords/assets/121855106/2a734a5d-6286-4e26-88e3-502688011b0b">




