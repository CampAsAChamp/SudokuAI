<div id="top"></div>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/CampAsAChamp/SudokuAI">
    <img src="images/logo.svg" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Sudoku AI</h3>

  <p align="center">
    Sudoku AI with Forward Checking, MRV, LCV and other heuristics and constraint propagation
    <br />
    <br />
    <a href="https://github.com/CampAsAChamp/SudokuAI">View Demo</a>
    ·
    <a href="https://github.com/CampAsAChamp/SudokuAI/issues">Report Bug</a>
    ·
    <a href="https://github.com/CampAsAChamp/SudokuAI/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#features">Features</a>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#heuristics">Heuristics</a></li>
    <li><a href="#P, Q, and M">P, Q, and M</a></li>
    <li><a href="#board-files-and-generation">Board Files and Generation</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

<div align="center">

![product-screenshot]

</div>

<p align="right">(<a href="#top">back to top</a>)</p>



### Built With

[![My Skills](https://skillicons.dev/icons?i=cpp)](https://skillicons.dev)

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

* **C++**
* **G++**

### Installation

1. Clone the repo
    ```sh
    git clone https://github.com/CampAsAChamp/SudokuAI.git
    ```
2. Build the executable
    ```sh
    make
    ```

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
### Usage

1. Run the solver with back tracking logic (default)
    ```sh
    bin/Sudoku
    ```
      1. The BackTracking Solver will have some basic backtracking logic already implemented at the start. 
      2. This logic should suffice to solve P = 3, Q = 3, matrices (More on P and Q below).
2. Run the solver with other heuristics
    ```sh
    bin/Sudoku MRV LCV
    ```
3. Run the solver with specified boards
    ```sh
    bin/Sudoku MRV LCV path/to/board/files
    ```
4. By default, a random 3x3 matrix will be generated and displayed. The solver will attempt to solve it, and the solution will be displayed once found. If no solution is found, a text message description appears. The number of assignments and backtracks made will also be displayed.
5. You add tokens on the command line to make your program run in different ways. List of Heuristics is below

### Heuristics
- **MRV**: Minimum Remaining Value Variable Selector
- **DEG**: Degree Heuristic Variable Selector
- **MAD**: MRV and DEG tie breaker
- **LCV**: Least Constraining Value Value Selector
- **FC**: Forward Checking Constraint Propagation
- **NOR**: Norvig's Sudoku Constraint Propagation
- **TOURN**: Custom Heuristic for tournament


## P, Q, and M
- N = the length of one side of the NxN grid, also the number of distinct tokens
- P = the number of rows in each block (Norvig's box is a synonym for block as used here)
- Q = the number of columns in each block
- M = the number of filled-in values at the start

Each block is a rectangle, P rows X Q columns. The set of blocks that align horizontally are called a block row (= a row of blocks). Similarly, the set of blocks that align vertically are called a block column (= a column of blocks).

`N = P*Q`, so `P = N/Q` and `Q = N/P`. Thus, there are P block columns and Q block rows. Please distinguish between rows/columns per block and block rows/block columns per grid. You can experiment by generating different board configurations with these parameters to see how they work.
 
`M = 0` is an empty sudoku board, and `M = 81` is a sudoku board with 81 values filled in. Note that higher values of M result in longer board generation times.



<p align="right">(<a href="#top">back to top</a>)</p>

## Board Files and Generation
You will have to generate and use Sudoku Board files throughout this project. This is made easy with the Board Generator. This should be found in the `Generator`. In there you can excute the make command to simply generate a set of custom boards. You can also use the board generator by the following synopsis:
```
python3 board_generator.py <File Prefix> <# of boards> <P> <Q> <M>
```
This will generate your desired boards. The file format is very simple, so you can custom the boards easily. The file format is:

P Q

&#35; &#35; &#35; ...

&#35; &#35; &#35; ...

&#35; &#35; &#35; ...

.

.

.

Where each **#** represents the value at that place on the board. If this is confusing, generate a file, and look at it.

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/CampAsAChamp/msPaintAutomation.svg?style=for-the-badge
[contributors-url]: https://github.com/CampAsAChamp/msPaintAutomation/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/CampAsAChamp/msPaintAutomation.svg?style=for-the-badge
[forks-url]: https://github.com/CampAsAChamp/msPaintAutomation/network/members
[stars-shield]: https://img.shields.io/github/stars/CampAsAChamp/msPaintAutomation.svg?style=for-the-badge
[stars-url]: https://github.com/CampAsAChamp/msPaintAutomation/stargazers
[issues-shield]: https://img.shields.io/github/issues/CampAsAChamp/msPaintAutomation.svg?style=for-the-badge
[issues-url]: https://github.com/CampAsAChamp/msPaintAutomation/issues
[license-shield]: https://img.shields.io/github/license/CampAsAChamp/msPaintAutomation.svg?style=for-the-badge
[license-url]: https://github.com/CampAsAChamp/msPaintAutomation/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[product-screenshot]: images/screenshot.png
