# Programming Contest Template Library - PrCoTeLi

This getting started guide assumes you are running Linux, and have a gcc compiler that can compile C++11 code.

### 0. Set up your GitHub account
If you don't have a GitHub account yet, set up one at https://github.com/join.

### 1. Fork PrCoTeLi master repository
Navigate to https://github.com/lukakalinovcic/prcoteli, and click on the Fork button in the upper right corner. You should now see the code at https://github.com/YOURACCOUNT/prcoteli.

### 2. Create your local repository, where you'll write your code
Open the terminal and position yourself into a local working directory.
```
  git clone https://github.com/YOURACCOUNT/prcoteli.git
  git remote add upstream https://github.com/lukakalinovcic/prcoteli.git
```
You should now see the "prcoteli" directory. This is your local copy of the code.

### 3. Concepts
This projects tries to capture data structures and algorithms that often appear in programming competitions as concepts, and implement those concepts as a template library.

Concepts are defined using text comments. For example:
```
// Array is a concept with these properties:
// * The type of contained values is defined as "value_type".
// * A default constructor with no arguments that creates an empty array.
// * A constructor with the initial size as an argument that creates an array of
//   that many elements.
// * Has the size() const method that returns an int or a value that
//   can be converted to int.
// * Has the operator[](int index) const method that returns the value or the
//   reference to the value at a given index.
```
Concepts usually come with a working non-optimal implementation, which you are advised to look at to better undestand the interface. For example, https://github.com/lukakalinovcic/prcoteli/blob/master/impl/kalinov/array/vector_backed_dynamic_array.hpp implements the DynamicArray interface.

In addition to that, for every concept SomeConcept we provide the struct IsSomeConcept, which uses Boost's concept check library to write checks which should primarily make your compilation error messages nicer, in case your interface doesn't match the specification. You don't have to understand or use the code that is written there.

Files in ```concepts/abstract/...``` define high level concepts that don't have a concrete implementation.  
For example, the Array concept above is an abstract concept, and there is no Array class to instantiate.

Files in ```concepts/concrete/...``` define concepts that we want to implement.  
For every concrete concept, we keep track of the "recommended" implementation. That is, among all implementation, we chose the best one. Most commonly we'll chose the fastest one.
The recommended implementation for a concept defined in ```concept/concrete/foo/bar.hpp``` is located in ```impl/concrete/foo/bar.hpp```.

Subscribe to https://groups.google.com/forum/#!forum/prcoteli-announce for announcements whenever a new concept is posted.

Discuss anything related to the concept at https://groups.google.com/forum/#!forum/prcoteli-discuss.

### 4. Your contribution
This is an open source project, which means that contributions from other people are welcome, and crucial to success. In fact, the recommended implementation will always refer to somebody's implementation. You may implement the concept just for practice, or you may implement it to be the fastest one available and become the recommended implementation for everybody else to use. Feel free to learn from other people's implementations.

Place your implementation files in your own directory, e.g. impl/YOURUSERNAME/concrete/foo/bar.hpp.

Most concepts will be announced together with test and benchmark suite, located in impl/concrete/foo/bar_test.hpp.

To test your implementation, simple edit impl/concrete/foo/bar.cpp.  
You should see #include directives for every existing implementation at the top. Add your implementation there.  
Below, you should TESTER_ADD_IMPLEMENTATION lines where tests for existing implentations are instantiated. Add your implementation there as well.

That's it. You can now run the test using the run_test.sh script in the root directory.
```
run_test.sh concrete/dynamic_array
```
To run tests for your implementation only type:
```
run_test.sh concrete/dynamic_array YOURUSERNAME
```

Once tests pass, you can run benchmarks to see how it performs against other implementations:
```
run_benchmarh.sh concrete/dynamic_array
```

To see every file that you have modified, added or removed, type:
```
git status
```
For every added file type:
```
git add path/to/file
```
Commit changes by typing:
```
git commit -m 'Some message describing the change' -a
```
Push changes to your github branch by typing:
```
git push -u origin master
```
You should now see changes at https://github.com/YOURACCOUNT/prcoteli. On the right side you can find the "Compare" link, which will once again show your contribution.

If you like what you see, you can create the pull request.  
I'll have a look at your changes, may comment if I see some problems, and finally I'll merge your changes into the master repository.

### 5. Syncing your repository with the master repository
```
git pull upstream master
```
You should now have the latest version of the master repository on your computer. If you made changes to a file that somebody else modified in the meantime, you'll have to resolve the conflict. The only file that multiple people should touch are _test.cpp files, which are quite simple, and conflicts should be trivial to resolve.

Your github repository will only be updated once you push to it.

### 6. Have fun

If you run into problems setting up your workspace, don't hesitate to write to https://groups.google.com/forum/#!forum/prcoteli-discuss.

This is still an early stage of the project, so please bear with me if something goes wrong. Also, please don't spread the word about this project just yet, as we first want to make sure everything is set up correctly.
