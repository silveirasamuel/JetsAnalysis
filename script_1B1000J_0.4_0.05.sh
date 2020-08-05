#!/bin/bash
#SBATCH --job-name=CSJets_1B1000J_0.4_0.05
#SBATCH --time=3-00:00:00
#SBATCH --ntasks=1
#SBATCH --array=1-1000
#SBATCH --output=output_1M1000J_0.4_0.05_%a.out
#SBATCH --error=errors_1M1000J_0.4_0.05_%a.err

module add gnu8/8.3.0
module load gnu8/8.3.0
module load root-6.16.00-gcc-8.3.0-ih7ao2c

echo -e "\n## Job iniciado em $(date +'%d-%m-%Y as %T') ###################"

cd $SLURM_SUBMIT_DIR
echo -e "\n## Diretorio de submissao do job: $SLURM_SUBMIT_DIR \n"

#CSAnalysis recebe como parâmetro a quantidade de simulações e os parâmetros físicos. Como recurso de saída 
#utiliza-se também o ID do job na lista e a quantidade de jobs no array.
srun ./CSAnalysis ggscbar 1000000 0.4 0.05 $SLURM_ARRAY_TASK_ID $SLURM_ARRAY_TASK_MAX

cd OUTPUT/Histograms_Output/
mkdir -p 1000000000_0.4_0.05_1000
cd ../../

#Estas análises são feitas no ROOT e retornam os histogramas das simulações do CSAnalysis.
srun root.exe -q "analysisJetsInvariantMass.C(1000000,0.4,0.05,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"
srun root.exe -q "analysisJetsQuarksPt.C(1000000,0.4,0.05,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"
srun root.exe -q "analysisMatchesCharmJets.C(1000000,0.4,0.05,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"

#Guarda-se os arquivos de saída numa pasta com as características do job e da simulação.
mkdir -p logs_1B_0.4_0.05_1000
mv output_1M1000J_0.4_0.05_$SLURM_ARRAY_TASK_ID.out logs_1B_0.4_0.05_1000/
mv errors_1M1000J_0.4_0.05_$SLURM_ARRAY_TASK_ID.err logs_1B_0.4_0.05_1000/

echo -e "\n## Job finalizado em $(date +'%d-%m-%Y as %T') ###################"
           
