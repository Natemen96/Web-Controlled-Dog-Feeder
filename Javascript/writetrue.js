var fso, f;
fso = new ActiveXObject("Scripting.FileSystemObject");
f = fso.CreateTextFile("../Python/feedme.txt", true);
f.WriteLine("This is a test.");
f.Close();
