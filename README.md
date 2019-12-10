# CS170 Project DTH

> Author: Yao Shao, Zhiyi Li, Huben Liu
>
> Contact:  yshao@gmail.com

## Reminder

- Please run on Windows since we only test it on Win10 and can't promise it works correctly on other OS.
- Don't change the names of the folders and files unless you know exactly what will happen.
- We use `python 3.7.4` and `stdc++11`, please make sure that your version is at least this. You may need to use `python3` instead of `python` in the terminal if you have installed multiple versions of python.
- We have write a automatic script in python which will generate the output in `.json` format. The result will be in the `utils`  folder. 
- Since we use a randomized algorithm, you may not get the exactly same answer as our submission. To get an output with similar quality, please repeate calling `auto.py` for about 15 times with approximately 30 hours in total.
- If you have any problems, please contact us by  yshao@gmail.com.

## Usage: A simple way

1. Before running, please install the dependencies by

   ```shell
   cd <path to the utils folder>
   pip3 install -r requirements.txt 
   ```

2. in terminal

   ```shell
   python first_generate.py ../inputs ../outputs_best
   ```

3. In terminal (repeat for about 15 times)

   ```
   python auto.py ../inputs ../outputs_new
   ```

   This script will firstly generate a new set of output files and store them in the outputs_new folder.  Then calculate the cost of each output and save them in the cost_new.log file. After that, we will compare the new cost with the current cost, replace the current output with the new one if the cost goes down. Finally, compress the best outputs to get the .json file.

## Alternative way

In case that you have any problem running `auto.py`, we also provide an alternative way though it is much more complex since you need to repeat this procedure for many times.

1. Before running, please install the dependencies by

   ```shell
   cd <path to the utils folder>
	pip3 install -r requirements.txt
   ```
   
2. in terminal

   ```shell
   python first_generate.py ../inputs ../outputs_best
   ```
   
3. create a folder named `outputs_new` in the root directory. Then in the `alg` folder, run `project_call.exe`

4. In terminal, change the working directory to `utils` 

   ```
   cd <path to the utils folder>
   ```

5. Calculate the cost

   ```shell
   python cost.py ../inputs ../outputs_new ../cost_new.log
   ```

6. Update the outputs

   ```shell
   python find_best_partial.py ../outputs_new ../cost_new.log
   ```

7. Compress the outputs

   ```shell
   python compress_output.py ../outputs_best/
   pip3 install requirments.txt
   python3 output_validator.py --all <path to input folder> <path to output folder>
   ```