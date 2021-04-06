echo "\033[33m(PIMSim): Building gem5... \033[0m"
scons -j16 build/X86/gem5.opt

echo "\033[33m(PIMSim): Compiling hellopim program... \033[0m"
g++ -o tests/test-progs/pim-hello/hellopim -O0 tests/test-progs/pim-hello/pim_test.cpp -I./include/ ./util/m5/m5op_x86.S

echo "\033[33m(PIMSim): Compiling macpim program... \033[0m"
g++ -o tests/test-progs/pim-hello/macpim -O0 tests/test-progs/pim-hello/pim_mac_test.cpp -I./include/ ./util/m5/m5op_x86.S

echo "\033[33m(PIMSim): Running... \033[0m"
#./build/X86/gem5.opt --debug-flags=PIM configs/example/se.py --cpu-type=TimingSimpleCPU --cpu-clock=2GHz --caches --l2cache --l1d_size=32kB --l1i_size=32kB --l2_size=2MB --l1d_assoc=4 --l1i_assoc=4 --l2_assoc=8 --enable-pim --pim-type=kernel --kernel-type=adder --num-pim-kernels=1 --mem-size=512MB --coherence-granularity=64B -c ./tests/test-progs/pim-hello/hellopim

#./build/X86/gem5.opt --debug-flags=PIM configs/example/se.py --cpu-type=TimingSimpleCPU --cpu-clock=2GHz --caches --l2cache --l1d_size=32kB --l1i_size=32kB --l2_size=2MB --l1d_assoc=4 --l1i_assoc=4 --l2_assoc=8 --enable-pim --pim-type=kernel --kernel-type=mac --num-pim-kernels=1 --mem-size=512MB --coherence-granularity=64B -c ./tests/test-progs/pim-hello/macpim

#./build/X86/gem5.opt --debug-flags=PIM configs/example/se.py --cpu-type=TimingSimpleCPU --cpu-clock=2GHz --caches --l2cache --l1d_size=32kB --l1i_size=32kB --l2_size=2MB --l1d_assoc=4 --l1i_assoc=4 --l2_assoc=8 --enable-pim --pim-type=kernel --kernel-type=adder --num-pim-kernels=1 --mem-size=1024MB --coherence-granularity=64B -c ../../PageRank/step2

./build/X86/gem5.opt --debug-flags=PIM configs/example/se.py --cpu-type=TimingSimpleCPU --cpu-clock=2GHz --caches --l2cache --l1d_size=32kB --l1i_size=32kB --l2_size=2MB --l1d_assoc=4 --l1i_assoc=4 --l2_assoc=8 --enable-pim --pim-type=kernel --kernel-type=mac --num-pim-kernels=1 --mem-size=1024MB --coherence-granularity=64B -c ../../PageRank/step2-PIM

#./build/X86/gem5.opt --debug-flags=PIM configs/example/se.py --cpu-type=TimingSimpleCPU --num-cpus=4 --cpu-clock=2GHz --caches --l2cache --l1d_size=32kB --l1i_size=32kB --l2_size=2MB --l1d_assoc=4 --l1i_assoc=4 --l2_assoc=8 --enable-pim --pim-type=kernel --kernel-type=adder --num-pim-kernels=1 --mem-size=1024MB --coherence-granularity=64B -c ../../PageRank/step3

### DO NOT USE BELOW, WILL NUKE SERVER!!!
#./build/X86/gem5.opt --debug-flags=PIM configs/example/se.py --cpu-type=TimingSimpleCPU --cpu-clock=2GHz --caches --l2cache --l1d_size=32kB --l1i_size=32kB --l2_size=2MB --l1d_assoc=4 --l1i_assoc=4 --l2_assoc=8 --enable-pim --pim-type=kernel --kernel-type=adder --num-pim-kernels=1 --mem-size=2048MB --coherence-granularity=64B -c /root/hostCurUser/Green-Marl/apps/output_cpp/bin/pagerank -o "/root/hostCurUser/Green-Marl/data/soc-LiveJournal1.bin 1"

