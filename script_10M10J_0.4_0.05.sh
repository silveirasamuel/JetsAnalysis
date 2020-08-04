#!/bin/bash
#SBATCH --job-name=CSJets_10M10J_0.4_0.05
#SBATCH --time=4-00:00:00
#SBATCH --ntasks=1
#SBATCH --array=1-10
#SBATCH --output=output_1M10J_0.4_0.05_%a.out
#SBATCH --error=errors_1M10J_0.4_0.05_%a.err

module add gnu8/8.3.0
module load gnu8/8.3.0
module load root-6.16.00-gcc-8.3.0-ih7ao2c

echo -e "\n## Job iniciado em $(date +'%d-%m-%Y as %T') ###################"

cd $SLURM_SUBMIT_DIR
echo -e "\n## Diretorio de submissao do job: $SLURM_SUBMIT_DIR \n"

srun ./CSAnalysis ggscbar 1000000 0.4 0.05 $SLURM_ARRAY_TASK_ID $SLURM_ARRAY_TASK_MAX

cd OUTPUT/Histograms_Output/
mkdir -p 10000000_0.4_0.05_10
cd ../../

srun root.exe -q "analysisJetsInvariantMass.C(1000000,0.4,0.05,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"
srun root.exe -q "analysisJetsQuarksPt.C(1000000,0.4,0.05,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"
srun root.exe -q "analysisMatchesCharmJets.C(1000000,0.4,0.05,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"

mkdir -p logs_10M_0.4_0.05_10
mv output_1M10J_0.4_0.05_$SLURM_ARRAY_TASK_ID.out logs_10M_0.4_0.05_10/
mv errors_1M10J_0.4_0.05_$SLURM_ARRAY_TASK_ID.err logs_10M_0.4_0.05_10/

echo -e "\n## Job finalizado em $(date +'%d-%m-%Y as %T') ###################"
           
