#!/bin/bash
#SBATCH --job-name=CSJets_1B1000J_0.4_0.15
#SBATCH -p long
#SBATCH --time=10-00:00:00
#SBATCH -n 128
#SBATCH --ntasks-per-node=64 
#SBATCH --output=output_1B1000J_0.4_0.15.out
#SBATCH --error=errors_1B1000J_0.4_0.15.err
#SBATCH --mail-user=samuel.silveira@aluno.ufabc.edu.br
#SBATCH --mail-type=ALL

module add gnu8/8.3.0
module load gnu8/8.3.0
module load root-6.16.00-gcc-8.3.0-ih7ao2c

echo -e "\n## Job iniciado em $(date +'%d-%m-%Y as %T') ###################"

cd $SLURM_SUBMIT_DIR
echo -e "\n## Diretorio de submissao do job: $SLURM_SUBMIT_DIR \n"

cd OUTPUT/Histograms_Output/
mkdir -p 1000000000_0.4_0.15_1000
cd ../../
mkdir -p logs_1B_0.4_0.15_1000

for i in {1..1000}
do
    srun -N1 -n1 -c1 --exclusive ./CSAnalysis ggscbar 1000000 0.4 0.15 $i 1000 > output_1M1000J_0.4_0.15_$i-1.out &
done
wait

for j in {1..1000}
do
    srun -N1 -n1 -c1 --exclusive root.exe -q "analysisJetsInvariantMass.C(1000000,0.4,0.15,$j,1000)" > output_1M1000J_0.4_0.15_$j-2.out &
done
wait

for k in {1..1000}
do
    srun -N1 -n1 -c1 --exclusive root.exe -q "analysisJetsQuarksPt.C(1000000,0.4,0.15,$k,1000)" > output_1M1000J_0.4_0.15_$k-3.out &
done
wait

for l in {1..1000}
do
    srun -N1 -n1 -c1 --exclusive root.exe -q "analysisMatchesCharmJets.C(1000000,0.4,0.15,$l,1000)" > output_1M1000J_0.4_0.15_$l-4.out &
done
wait   

for p in {1..1000}
do
    mv output_1M1000J_0.4_0.15_$p-*.out logs_1B_0.4_0.15_1000/ &
done
wait


mv output_1B1000J_0.4_0.15.out logs_1B_0.4_0.15_1000/
mv errors_1B1000J_0.4_0.15.err logs_1B_0.4_0.15_1000/


echo -e "\n## Job finalizado em $(date +'%d-%m-%Y as %T') ###################"