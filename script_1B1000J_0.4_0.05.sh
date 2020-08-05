#!/bin/bash
#SBATCH --job-name=CSJets_1B100J_0.4_0.05
#SBATCH -p long
#SBATCH --time=14-00:00:00
#SBATCH -n 64
#SBATCH --ntasks-per-node=64 
#SBATCH --output=output_1B100J_0.4_0.05.out
#SBATCH --error=errors_1B100J_0.4_0.05.err
#SBATCH --mail-user=samuel.silveira@aluno.ufabc.edu.br
#SBATCH --mail-type=ALL

module add gnu8/8.3.0
module load gnu8/8.3.0
module load root-6.16.00-gcc-8.3.0-ih7ao2c

echo -e "\n## Job iniciado em $(date +'%d-%m-%Y as %T') ###################"

cd $SLURM_SUBMIT_DIR
echo -e "\n## Diretorio de submissao do job: $SLURM_SUBMIT_DIR \n"

cd OUTPUT/Histograms_Output/
mkdir -p 1000000000_0.4_0.05_100
cd ../../
mkdir -p logs_1B_0.4_0.05_100

for i in {1..100}
do
    srun -N1 -n1 -c1 --exclusive ./CSAnalysis ggscbar 10000000 0.4 0.05 $i 100 > output_10M100J_0.4_0.05_$i-1.out &
done
wait

for j in {1..100}
do
    srun -N1 -n1 -c1 --exclusive root.exe -q "analysisJetsInvariantMass.C(10000000,0.4,0.05,$j,100)" > output_10M100J_0.4_0.05_$j-2.out &
done
wait

for k in {1..100}
do
    srun -N1 -n1 -c1 --exclusive root.exe -q "analysisJetsQuarksPt.C(10000000,0.4,0.05,$k,100)" > output_10M100J_0.4_0.05_$k-3.out &
done
wait

for l in {1..100}
do
    srun -N1 -n1 -c1 --exclusive root.exe -q "analysisMatchesCharmJets.C(10000000,0.4,0.05,$l,100)" > output_10M100J_0.4_0.05_$l-4.out &
done
wait   

for p in {1..100}
do
    mv output_10M100J_0.4_0.05_$p-*.out logs_1B_0.4_0.05_100/ &
done
wait


mv output_1B100J_0.4_0.05.out logs_1B_0.4_0.05_100/
mv errors_1B100J_0.4_0.05.err logs_1B_0.4_0.05_100/


echo -e "\n## Job finalizado em $(date +'%d-%m-%Y as %T') ###################"