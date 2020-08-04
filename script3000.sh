#!/bin/bash
#SBATCH --job-name=CSJets_3000_0.4_0.15
#SBATCH --time=01:00:00
#SBATCH --ntasks=1
#SBATCH --array=1-10
#SBATCH --output=output_300_0.4_0.15_%a.out
#SBATCH --error=errors_300_0.4_0.15_%a.err

module add gnu8/8.3.0
module load gnu8/8.3.0
module load root-6.16.00-gcc-8.3.0-ih7ao2c

echo -e "\n## Job iniciado em $(date +'%d-%m-%Y as %T') ###################"

cd $SLURM_SUBMIT_DIR
echo -e "\n## Diretorio de submissao do job: $SLURM_SUBMIT_DIR \n"

srun ./CSAnalysis ggscbar 300 0.4 0.15 $SLURM_ARRAY_TASK_ID $SLURM_ARRAY_TASK_MAX

cd OUTPUT/Histograms_Output/
mkdir -p 3000_0.4_0.15_10
cd ../../

srun root.exe -q "analysisJetsInvariantMass.C(300,0.4,0.15,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"
srun root.exe -q "analysisJetsQuarksPt.C(300,0.4,0.15,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"
srun root.exe -q "analysisMatchesCharmJets.C(300,0.4,0.15,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"

mkdir -p logs_3000_0.4_0.15_10
mv output_300_0.4_0.15_$SLURM_ARRAY_TASK_ID.out logs_3000_0.4_0.15_10/
mv errors_300_0.4_0.15_$SLURM_ARRAY_TASK_ID.err logs_3000_0.4_0.15_10/

echo -e "\n## Job finalizado em $(date +'%d-%m-%Y as %T') ###################"
           
Internacional1.