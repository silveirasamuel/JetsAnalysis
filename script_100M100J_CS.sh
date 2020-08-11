#!/bin/bash
#SBATCH --job-name=CSQuarks_100M100J
#SBATCH -p serial
#SBATCH --time=3-00:00:00
#SBATCH --ntasks=1
#SBATCH --array=1-100
#SBATCH --output=output_W_1M100J_%a.out
#SBATCH --error=errors_W_1M100J_%a.err
#SBATCH --mail-user=samuel.silveira@aluno.ufabc.edu.br
#SBATCH --mail-type=ALL

module add gnu8/8.3.0
module load gnu8/8.3.0
module load root-6.16.00-gcc-8.3.0-ih7ao2c

echo -e "\n## Job iniciado em $(date +'%d-%m-%Y as %T') ###################"

cd $SLURM_SUBMIT_DIR
echo -e "\n## Diretorio de submissao do job: $SLURM_SUBMIT_DIR \n"

srun ./CSAnalysis_Quarks ggscbar 1000000 $SLURM_ARRAY_TASK_ID $SLURM_ARRAY_TASK_MAX

cd OUTPUT_CS/Histograms_Output/
mkdir -p 100000000_100
cd ../../

srun root.exe -q "analysisQuarksInvariantMass.C(1000000,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"

mkdir -p logs_W_100M_100
mv output_W_1M100J_$SLURM_ARRAY_TASK_ID.out logs_W_100M_100/
mv errors_W_1M100J_$SLURM_ARRAY_TASK_ID.err logs_W_100M_100/

cd OUTPUT_CS/Histograms_Output/100000000_100
hadd -f 100M_WInvariantMass.root *hresultsWInvariantMass.root

echo -e "\n## Job finalizado em $(date +'%d-%m-%Y as %T') ###################"
           
